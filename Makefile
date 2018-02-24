CUR_WORKING_DIR!=pwd
OUT_DIR=deps_dir
TMP_DIR=.tmp_dir
LIBS_DEPENDENCIES_DIR=$(CUR_WORKING_DIR)

.PHONY: all clean install_libs

all:
	make install_libs

install_libs: _install_dependencies

clean: # remove libs and headers files
	rm -rf include lib


# Target that are usefull for other targets
# don't edit!

.PHONY: _download_libs_src _deps_dir _expat _zlib _libzip _openssl _bzip2 _xlsxio

_install_dependencies:
	mkdir $(TMP_DIR)
	cp Makefile $(TMP_DIR)
	cd $(TMP_DIR); make _download_libs_src
	cd $(TMP_DIR); make _deps_dir
	cd $(TMP_DIR); make _expat
	cd $(TMP_DIR); make _zlib
	cd $(TMP_DIR); make _bzip2
	cd $(TMP_DIR); make _openssl
	cd $(TMP_DIR); make _libzip
	cd $(TMP_DIR); make _xlsxio
	mv $(TMP_DIR)/$(OUT_DIR)/* .
	cd $(TMP_DIR); make _clear
	rm -rf $(TMP_DIR)


_download_libs_src:
	git clone https://github.com/brechtsanders/xlsxio
	git clone https://github.com/nih-at/libzip
	git clone https://github.com/libexpat/libexpat
	git clone https://github.com/openssl/openssl
	curl -o bzip2.tar.gz bzip.org/1.0.6/bzip2-1.0.6.tar.gz # download and extract bzip2 for libzip
	tar -xvf bzip2.tar.gz
	mv bzip2-1.0.6 bzip2
	rm -rf bzip2.tar.gz
	curl -o zlib.tar.gz www.zlib.net/zlib-1.2.11.tar.gz # download and extract zlib for libzip
	tar -xvf zlib.tar.gz
	mv zlib-1.2.11 zlib
	rm -rf zlib.tar.gz

_deps_dir:
	mkdir $(OUT_DIR)
	mkdir $(OUT_DIR)/include
	mkdir $(OUT_DIR)/lib

_expat: # create libexpat for xml parsing
	cd libexpat/expat; mkdir build; cd build; cmake -DWINCE=ON -DBUILD_tools=OFF -DBUILD_examples=OFF -DBUILD_tests=OFF -DBUILD_shared=OFF -DBUILD_doc=OFF ..; make; make install DESTDIR=.
	cp libexpat/expat/build/usr/local/include/*.h $(OUT_DIR)/include/
	cp libexpat/expat/build/usr/local/lib64/*.a $(OUT_DIR)/lib/

_zlib: # create libz for libzip as dependency
	cd zlib; mkdir build; cd build; cmake ..; make; make install DESTDIR=.
	cp zlib/build/usr/local/include/*.h $(OUT_DIR)/include/
	cp zlib/build/usr/local/lib/*.a $(OUT_DIR)/lib/

_bzip2: # create libbz2 for libzip as dependency
	cd bzip2; mkdir build; make; make install PREFIX=./build
	cp bzip2/build/include/*.h $(OUT_DIR)/include/
	cp bzip2/build/lib/*.a $(OUT_DIR)/lib/

_openssl: # create libssl for libzip as dependency
	cd openssl; mkdir build; ./config --prefix=$(LIBS_DEPENDENCIES_DIR)/openssl/build/; make; make install;
	cp -r openssl/build/include/* $(OUT_DIR)/include/
	cp openssl/build/lib/*.a $(OUT_DIR)/lib/

_libzip: # create libzip for libxlsxio
	cd libzip; mkdir build; cd build; cmake .. -DBUILD_SHARED_LIBS=OFF -DCMAKE_INSTALL_PREFIX=.; make; make install
	cp libzip/build/include/*.h $(OUT_DIR)/include/
	cp libzip/build/lib/*.a $(OUT_DIR)/lib/

_xlsxio: # create libxlsxio_read and libxlsxio_write for work with .xlsx files
	cd xlsxio; mkdir build; cd build; cmake .. -DBUILD_SHARED=OFF -DBUILD_TOOLS=OFF -DBUILD_EXAMPLES=OFF -DCMAKE_INSTALL_PREFIX=.; make; make install
	cp xlsxio/build/include/*.h $(OUT_DIR)/include/
	cp xlsxio/build/lib/*.a $(OUT_DIR)/lib/

_clear: # remove all files but not libs and headers
	rm -rf xlsxio libzip libexpat zlib openssl bzip2 $(OUT_DIR)
