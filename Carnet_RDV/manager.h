#ifndef MANAGER_H
#define MANAGER_H

#include "date.h"
#include "hour.h"
#include "ldcp.h"
#include "ldcr.h"

#include <QProgressBar>

#include <fstream>
#include <sstream>

// Fonctions annexes
bool isStringEmpty(const string& s);

const static string     FILENAMEPERSONNE = "Personne.carnetRDV";
const static string     FILENAMERDV = "RDV.carnetRDV";
const static QString    QFILENAMEPERSONNE = "Personne.carnetRDV";
const static QString    QFILENAMERDV = "RDV.carnetRDV";

class Manager
{
private:
    LDCP listPersonnes;
    LDCR listRDV;

public:
    enum AddPersonneToOrRemovePersonneFromRdv {PersonneAdded = 1, PersonneRemoved, PersonneHasAnRdv, PersonneIsAlreadyInsideRdv, PersonneHasNotBeenAdded, PersonneHasNotBeenRemoved, RdvListIsEmpty,
                                                   RdvAdded, RdvRemoved, RdvHasNotBeenAdded, RdvHasNotBeenRemoved, MembersListIsEmpty,
                                                   RdvNotFound, PersonneNotFound, PersonneAndRdvNotFound, };

    Manager(void);

    // Méthodes
    bool            addPersonne(Personne* p);
    int             addPersonneToRDV(const string& rdvName, const string& pFirstName, const string& pLastName);
    bool            addRDV(RDV* rdv);
    bool            changeDateAndHour(RDV* r, const Date& d, const Hour& hd, const Hour& hf);
    void            changeMail(Personne* p, const string& mail);
    void            changePhone(Personne* p, const string& numeroTel);
    void            changePhoneAndMail(Personne* p, const string& numeroTel, const string& mail);
    bool            loadPersonne(const string& filePath = "", QProgressBar* loadingBar = nullptr);
    bool            loadRDV(const string& filePath = "", QProgressBar* loadingBar = nullptr);
    vector<RDV*>    rechRdvDate(const Date& d);
    int             removePersonne(Personne* p);
    int             removePersonneFromRDV(const string& rdvName, const string& pFirstName, const string& pLastName);
    bool            removeRDV(RDV* rdv);
    bool            savePersonne(const string& filePath = "", QProgressBar* loadingBar = nullptr);
    bool            saveRDV(const string& filePath = "", QProgressBar* loadingBar = nullptr);

    // Getters
    const LDCP& getListPersonnes(void) const;
    const LDCR& getListRDV(void) const;

};

#endif // MANAGER_H
