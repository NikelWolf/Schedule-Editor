#pragma once

#include <common.h>

using namespace std;

namespace schedule_api {
    class Lesson {
    public:
        Lesson(): _subject_name{}, _lesson_type{}, _professor{}, _room{}, _additions{} {}

        Lesson(string subject_name, string lesson_type, string professor, string room):
                _subject_name{move(subject_name)}, _lesson_type{move(lesson_type)},
                _professor{move(professor)}, _room{move(room)}, _additions{} {}

        Lesson(const Lesson &lesson) noexcept {
            _subject_name = lesson._subject_name;
            _lesson_type = lesson._lesson_type;
            _professor = lesson._professor;
            _room = lesson._room;
            _additions = lesson._additions;
        }

        Lesson(Lesson &&lesson) noexcept {
            _subject_name = lesson._subject_name;
            _lesson_type = lesson._lesson_type;
            _professor = lesson._professor;
            _room = lesson._room;
            _additions = lesson._additions;
        }

        virtual ~Lesson() = default;

        Lesson &operator=(const Lesson &lesson) = default;

        Lesson &operator=(Lesson &&lesson) = default;

        const string &get_subject_name() const {
            return _subject_name;
        }

        void set_subject_name(const string &subject_name) {
            _subject_name = subject_name;
        }

        const string &get_lesson_type() const {
            return _lesson_type;
        }

        void set_lesson_type(const string &lesson_type) {
            _lesson_type = lesson_type;
        }

        const string &get_professor() const {
            return _professor;
        }

        void set_professor(const string &professor) {
            _professor = professor;
        }

        const string &get_room() const {
            return _room;
        }

        void set_room(const string &room) {
            _room = room;
        }

        void set_additions(const vector<string> &additions) {
            _additions = additions;
        }

        void add_addition(const string &addition) {
            _additions.push_back(const_cast<string &>(addition));
        }

        void add_additions(const vector<string> &additions) {
            for (const string &addition: additions) {
                _additions.push_back(addition);
            }
        }

        const vector<string> &get_additions() const {
            return _additions;
        }

        string to_string(const string &intends="\n\t") const {

            string str_lesson = "Lesson: {" + intends +
                                          "\tsubject: \"" + _subject_name + "\"," + intends +
                                          "\ttype: \"" + _lesson_type + "\"," + intends +
                                          "\tprofessor: \"" + _professor + "\"," + intends +
                                          "\troom: \"" + _room + "\"," + intends +
                                          "\tadditions: [";
            for (int i = 0; i < _additions.size(); i++) {
                str_lesson += intends + "\t\t\"" + _additions[i] + (i != _additions.size() - 1 ? "\"," : "\"");
            }
            str_lesson += intends + "\t]" + intends + "}";
            return str_lesson;
        }

        friend ostream &operator<<(ostream &os, const Lesson &lesson);

    private:
        string _subject_name;
        string _lesson_type;
        string _professor;
        string _room;
        vector<string> _additions;
    };

    ostream &operator<<(ostream &os, const Lesson &lesson) {
        os << lesson.to_string();
        return os;
    }
}
