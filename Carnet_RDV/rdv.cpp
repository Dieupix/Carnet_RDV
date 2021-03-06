#include "rdv.h"

RDV::RDV(const string& name, const Date& date, const Hour& timeStart, const Hour& timeEnd, const vector<Personne*>& membersList){
    this->name = name;
    this->date = date;
    this->timeStart = timeStart;
    this->timeEnd = timeEnd;
    this->membersList = membersList;
}



// ---------- Surcharge des opérateurs ----------
bool RDV::operator>(const RDV& rdv) const{
    return compareTo(rdv) < 0;
}
bool RDV::operator>=(const RDV& rdv) const{
    return compareTo(rdv) <= 0;
}
bool RDV::operator<(const RDV& rdv) const{
    return compareTo(rdv) > 0;
}
bool RDV::operator<=(const RDV& rdv) const{
    return compareTo(rdv) >= 0;
}
bool RDV::operator==(const RDV& rdv) const{
    return compareTo(rdv) == 0;
}
bool RDV::operator!=(const RDV& rdv) const{
    return compareTo(rdv) != 0;
}

void RDV::operator=(const RDV& rdv){
    this->name = rdv.name;
    this->date = rdv.date;
    this->timeStart = rdv.timeStart;
    this->timeEnd = rdv.timeEnd;
    this->membersList = rdv.membersList;
}

RDV::operator QString(void) const{
    return toQString();
}
RDV::operator string(void) const{
    return toString();
}



// ---------- Méthodes ----------
/* Retourne :
 * PersonneIsAlreadyInsideRdv si la personne est déjà dans le RDV
 * PersonneAdded si la personne a pu être ajoutée
 * Personne::addRDV() sinon
*/
int RDV::addMember(Personne* p)
{
    unsigned i{0};
    while(i < membersList.size())
        if(*p == *membersList[i++])
            return PersonneIsAlreadyInsideRdv;

    int addRDVtoP = p->addRDV(this);
    if(addRDVtoP == RdvAdded){
        if(membersList.size() == 0)
            membersList.push_back(p);

        else{
            membersList.push_back(membersList[membersList.size() - 1]);
            unsigned j = 0;
            for(j = membersList.size() - 2; j > i; --j)
                membersList[j] = membersList[j - 1];

            membersList[j] = p;
        }
        return PersonneAdded;
    }else return addRDVtoP;
}

void RDV::afficher(ostream& ost) const{
    ost << toString();
}

// Retourne 1 si r > à this, -1 si r < this, 0 sinon
int RDV::compareTo(const RDV& r ) const
{
    string thisN = name, rN = r.name;
    for(unsigned i = 0; i < thisN.length(); ++i) thisN[i] = toupper(thisN[i]);
    for(unsigned i = 0; i < rN.length(); ++i) rN[i] = toupper(rN[i]);

    if(thisN > rN) return -1;
    else if(thisN < rN) return 1;
    else return 0;
    /* if(date > r.date) return -1;
    else if(date < r.date) return 1;
    else if(timeStart > r.timeStart) return -1;
    else if(timeStart < r.timeStart) return 1;
    else if(timeEnd > r.timeEnd)  return -1;
    else if(timeEnd < r.timeEnd) return 1;
    else return 0;*/

}

bool RDV::estImbrique(const RDV& r) const
{
    if(date == r.date)
    {
        if(timeStart == r.timeStart || timeEnd == r.timeEnd)
        {
            return true;
        }
        else if(timeStart < r.timeStart && timeEnd > r.timeStart)
        {
            return true;
        }
        else if(timeStart > r.timeStart && r.timeEnd > timeStart)
        {
            return true;
        }
    }
    return false;
}

QString RDV::participantsToQString(void){
    return QString::fromStdString(participantsToString());
}

string RDV::participantsToString(void){
    string s = QString(QObject::tr("Participant", "Participant", membersList.size())).toStdString() + string(membersList.size() == 1 ? "" : "s") + " " +
            "(" + to_string(membersList.size()) + ") :\n";
    if (membersList.size() == 0) s += QString(QObject::tr("Aucun participant", "Any participant")).toStdString() + "\n";
    else for(unsigned i = 0; i < membersList.size(); ++i) s += membersList[i]->toString() + "\n";
    return s;
}

/* Retourne :
 * MembersListIsEmpty s'il n'y a pas de participants à supprimer
 * PersonneRemoved s'il a pu être enlevé
 * PersonneHasNotBeenRemoved s'il y a eu un problème
 * Personne::removeRDV() sinon
*/
int RDV::removeMember(Personne* p)
{
    unsigned i{0};
    bool found = false;
    while(i < membersList.size() and ! found){
        if(*p == *membersList[i]) found = true;
        else ++i;
    }
    int removeRDVFromP = p->removeRDV(this);
    if(removeRDVFromP == RdvRemoved)
    {
        if(membersList.size() < 2) return MembersListIsEmpty;
        else if(found){
            for(unsigned j = i; j < membersList.size() - 1; ++j)
                membersList[j] = membersList[j + 1];
            membersList.pop_back();
            return PersonneRemoved;
        }else return PersonneHasNotBeenRemoved;
    }else return removeRDVFromP;
}

QString RDV::toQString(void) const{
    return QString::fromStdString(toString());
}

string RDV::toString(void) const{
    string s = name +
            " - Le " + date.toString() +
            " - De " + timeStart.toString() +
            " à " + timeEnd.toString();
    return s;
}



// ---------- Getters ----------
const string& RDV::getName(void) const{
    return this->name;
}
const Date& RDV::getDate(void) const{
    return this->date;
}
const Hour& RDV::getTimeStart(void) const{
    return this->timeStart;
}
const Hour& RDV::getTimeEnd(void) const{
    return this->timeEnd;
}
const vector<Personne*>& RDV::getMembersList(void) const{
    return this->membersList;
}



// ---------- Setters ----------
void RDV::setName(const string& name){
    this->name = name;
}
void RDV::setDate(const Date& date){
    this->date = date;
}
void RDV::setTimeStart(const Hour& timeStart){
    this->timeStart = timeStart;
}
void RDV::setTimeEnd(const Hour& timeEnd){
    this->timeEnd = timeEnd;
}
void RDV::setMembersList(const vector<Personne*>& membersList){
    this->membersList = membersList;
}



// ---------- Fonctions globales ----------
ostream& operator<<(ostream& ost, const RDV& rdv){
    rdv.afficher(ost);
    return ost;
}
