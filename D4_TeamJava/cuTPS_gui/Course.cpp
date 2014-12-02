/*Course class source file
 *
 *Traceability: EO-08
 *
 *
 */
#include "Course.h"


//Constructor
Course::Course(QString cCode, QString section, QString instruct) :
    courseCode(cCode), courseSection(section), instructor(instruct){
    term = new Term();
}

//Students and Textbooks persist after a Course is deleted
Course::~Course(){
    delete term;
}

//GETTERS
QString Course::getCourseCode()                    const{return courseCode;}
QString Course::getCourseSection()                 const{return courseSection;}
Term*   Course::getTerm()                          const{return term;}
QString Course::getInstructor()                    const{return instructor;}
QList<Student*>& Course::getRegisteredStudents()        {return students;}
QList<Textbook*>& Course::getRequiredTextbooks()        {return requiredTextbooks;}

//SETTERS
void Course::setCourseCode(QString c){courseCode = c;}
void Course::setCourseSection(QString s){courseSection = s;}
void Course::setTerm(Term* t){
    delete term;
    term = t;
}
void Course::setInstructor(QString i){instructor = i;}

//Adds a Student to the Course
void Course::addStudent(Student* student){
    students.push_back(student);
}

//Adds a Textbook to the Course
void Course::addTextbook(Textbook* textbook){
    requiredTextbooks.push_back(textbook);
}

//READ AND WRITE FUNCTIONS FOR JSON

//Read json object and set course's attributes to match
void Course::read(const QJsonObject &json){

    //Setting primitive attributes from JSON
    courseCode = json["courseCode"].toString();
    courseSection = json["courseSection"].toString();
    instructor = json["instructor"].toString();

    //Let Course's term read json key "term" as a JSONobject
    term->read(json["term"].toObject());

    //Clear existing students within array: TODO properly delete pointers
    students.clear();
    //Read "students" key as a JSON array and add it to students list
    QJsonArray studentArray = json["students"].toArray();
    for(int studentIndex = 0; studentIndex < studentArray.size(); ++studentIndex){
        QJsonObject studentObject = studentArray[studentIndex].toObject();
        Student* newStu = new Student();
        newStu->read(studentObject);
        students.append(newStu);
    }

    //Clear existing required textbooks within array: TODO properly delete pointers
    requiredTextbooks.clear();
    //Read "requiredTextbooks" key as a JSOn array and add it to textbooks list
    QJsonArray textbookArray = json["requiredTextbooks"].toArray();
    for(int textIndex = 0; textIndex < textbookArray.size(); ++textIndex){
        QJsonObject textbookObject = textbookArray[textIndex].toObject();
        Textbook* newTextbook = new Textbook();
        newTextbook->read(textbookObject);
        requiredTextbooks.append(newTextbook);
    }
}

//Write coruse's attributes to a json object
void Course::write(QJsonObject &json) const{

    //Writing primitive attributes to JSON
    json["courseCode"] = courseCode;
    json["courseSection"] = courseSection;
    json["instructor"] = instructor;

    //Writing a term as a json object
    QJsonObject t;
    term->write(t);
    json["term"] = t;

    QJsonArray studentArray;
    foreach (const Student* stu, students){
        QJsonObject stuObject;
        stu->write(stuObject);
        studentArray.append(stuObject);
    }
    json["students"] = studentArray;

    QJsonArray textbookArray;
    foreach (const Textbook* text, requiredTextbooks){
        QJsonObject textbookObject;
        text->write(textbookObject);
        textbookArray.append(textbookObject);
    }
    json["requiredTextbooks"] = textbookArray;


}

std::ostream& operator<<(std::ostream& o,  Course& course){
    return o << course.getCourseCode().toStdString() << "-" << course.getCourseSection().toStdString() << endl
      << "course.getTerm()"
      << "Instructor: ";
}
