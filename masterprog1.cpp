#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <limits>
#include <algorithm>
#include <sstream>
#include <cctype>   // for isalpha, tolower
#include <cstdlib> // for atof, atoi

using namespace std;

// validationw
string readLineTrim() {
    string s;
    getline(cin, s);
    // trim both ends
    string::size_type l = s.find_first_not_of(" \t\r\n");
    if (l == string::npos) return "";
    string::size_type r = s.find_last_not_of(" \t\r\n");
    return s.substr(l, r - l + 1);
}

bool isDigitsOnly(const string &s) {
    if (s.empty()) return false;
    for (string::size_type i = 0; i < s.length(); ++i) {
        if (s[i] < '0' || s[i] > '9') return false;
    }
    return true;
}

bool isAlphaOrSpace(const string &s) {
    if (s.empty()) return false;
    for (string::size_type i = 0; i < s.length(); ++i) {
        if (!isalpha(s[i]) && s[i] != ' ') return false;
    }
    return true;
}

double parseDouble(const string &s) {
    if (s.empty()) return -1;
    bool dot = false;
    for (string::size_type i = 0; i < s.length(); ++i) {
        char c = s[i];
        if (c == '.') {
            if (dot) return -1;
            dot = true;
        } else if (c < '0' || c > '9') {
            return -1;
        }
    }
    return atof(s.c_str());
}

string toLower(string s) {
    for (string::size_type i = 0; i < s.length(); ++i) {
        s[i] = (char)tolower(s[i]);
    }
    return s;
}

void pause() {
    cout << "\nPress Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// ---------- Base classes ----------
class Person {
protected:
    string name;
    int age;
public:
    Person() : age(0) {}
    virtual ~Person() {}
    void inputBasic() {
        while (true) {
            cout << "Enter name: ";
            string s = readLineTrim();
            if (isAlphaOrSpace(s)) { name = s; break; }
            cout << "Invalid name (letters & spaces only).\n";
        }
        while (true) {
            cout << "Enter age: ";
            string s = readLineTrim();
            if (s.empty()) { age = 0; break; }
            if (isDigitsOnly(s)) { age = atoi(s.c_str()); break; }
            cout << "Invalid age (digits only).\n";
        }
    }
    virtual void displayBasic() const {
        cout << left << setw(16) << "Name" << ": " << name << "\n";
        cout << left << setw(16) << "Age" << ": " << age << "\n";
    }
    int getAge() const { return age; }
    string getName() const { return name; }
};

// ---------- Patient classes ----------
class Patient : public Person {
protected:
    string patientID;
    string illness;
    string severity; // high/medium/low
    double totalPaid;
public:
    static int patientCounter;
    Patient() : totalPaid(0.0) { patientCounter++; }
    virtual ~Patient() {}
    virtual void input() {
        inputBasic();
        while (true) {
            cout << "Patient ID (digits only): ";
            string s = readLineTrim();
            if (isDigitsOnly(s)) { patientID = s; break; }
            cout << "Invalid ID.\n";
        }
        cout << "Illness (single-line): ";
        illness = readLineTrim();
        while (true) {
            cout << "Severity (high/medium/low): ";
            string s = toLower(readLineTrim());
            if (s == "high" || s == "medium" || s == "low") { severity = s; break; }
            cout << "Enter high, medium, or low.\n";
        }
    }
    virtual void billing() {
        cout << "Enter total amount paid for this patient: ";
        while (true) {
            string s = readLineTrim();
            double v = parseDouble(s);
            if (v >= 0) { totalPaid = v; break; }
            cout << "Invalid amount. Try again.\n";
        }
    }
    virtual void displayBasicInfo() const {
        cout << "Patient ID   : " << patientID << "\n";
        displayBasic();
        cout << left << setw(16) << "Illness" << ": " << illness << "\n";
        cout << left << setw(16) << "Severity" << ": " << severity << "\n";
        cout << left << setw(16) << "Total Paid" << ": " << fixed << setprecision(2) << totalPaid << "\n";
    }
    double getTotalPaid() const { return totalPaid; }
    string getSeverity() const { return severity; }
    string suggestDepartment() const {
        string low = toLower(illness);

        // Cardiology
        if (low.find("heart") != string::npos || low.find("cardiac") != string::npos || low.find("chest pain") != string::npos || low.find("arrhythmia") != string::npos) {
            return "Cardiology";
        }
        // Orthopedics
        if (low.find("fracture") != string::npos || low.find("bone") != string::npos || low.find("joint pain") != string::npos || low.find("sprain") != string::npos || low.find("dislocation") != string::npos) {
            return "Orthopedics";
        }
        // Neurology
        if (low.find("headache") != string::npos || low.find("migraine") != string::npos || low.find("seizure") != string::npos || low.find("stroke") != string::npos || low.find("numbness") != string::npos) {
            return "Neurology";
        }
        // ENT
        if (low.find("earache") != string::npos || low.find("throat pain") != string::npos || low.find("hearing loss") != string::npos || low.find("sinus") != string::npos || low.find("nose") != string::npos) {
            return "ENT (Ear, Nose, Throat)";
        }
        // Dermatology
        if (low.find("skin rash") != string::npos || low.find("eczema") != string::npos || low.find("acne") != string::npos || low.find("dermatitis") != string::npos) {
            return "Dermatology";
        }
        // Gastroenterology
        if (low.find("stomach") != string::npos || low.find("digestive") != string::npos || low.find("acid reflux") != string::npos || low.find("ulcer") != string::npos) {
            return "Gastroenterology";
        }
        // Pulmonology
        if (low.find("breathing") != string::npos || low.find("asthma") != string::npos || low.find("lung") != string::npos || low.find("bronchitis") != string::npos) {
            return "Pulmonology";
        }
        // General Medicine (fallback)
        if (low.find("fever") != string::npos || low.find("cold") != string::npos || low.find("flu") != string::npos || low.find("cough") != string::npos) {
            return "General Medicine";
        }

        return "General Medicine (Unclassified)";
    }
    void riskAnalysis() const {
        cout << "\n--- Risk Analysis ---\n";
        if (severity == "high" && age >= 60) cout << "Risk Level: CRITICAL - immediate attention needed.\n";
        else if (severity == "high") cout << "Risk Level: HIGH - urgent care advised.\n";
        else if (severity == "medium" || age >= 45) cout << "Risk Level: MODERATE - monitor closely.\n";
        else cout << "Risk Level: LOW - routine care.\n";
    }
};
int Patient::patientCounter = 0;

class InPatient : public Patient {
    int daysAdmitted;
    double roomChargePerDay;
    double finalBill;
public:
    InPatient() : daysAdmitted(0), roomChargePerDay(0.0), finalBill(0.0) {}
    void input() {
        Patient::input();
        while (true) {
            cout << "Days admitted (digits): ";
            string s = readLineTrim();
            if (isDigitsOnly(s)) { daysAdmitted = atoi(s.c_str()); break; }
            cout << "Invalid number.\n";
        }
        while (true) {
            cout << "Room charge per day: ";
            string s = readLineTrim();
            double v = parseDouble(s);
            if (v >= 0) { roomChargePerDay = v; break; }
            cout << "Invalid amount.\n";
        }
        billing();
    }
    void billing() {
        cout << "Enter doctor fee: ";
        double doctorFee = 0.0;
        while (true) {
            string s = readLineTrim();
            double v = parseDouble(s);
            if (v >= 0) { doctorFee = v; break; }
            cout << "Invalid amount.\n";
        }
        finalBill = doctorFee + daysAdmitted * roomChargePerDay;
        if (age < 12) finalBill *= 0.5;
        else if (age > 60) finalBill *= 0.7;
        totalPaid = finalBill;
    }
    void displayFull(int index) const {
        cout << "\n--- IN-PATIENT RECORD #" << index+1 << " ---\n";
        displayBasicInfo();
        cout << left << setw(20) << "Days Admitted" << ": " << daysAdmitted << "\n";
        cout << left << setw(20) << "Room Charge/Day" << ": " << fixed << setprecision(2) << roomChargePerDay << "\n";
        cout << left << setw(20) << "Final Bill" << ": " << fixed << setprecision(2) << finalBill << "\n";
        cout << left << setw(20) << "Department" << ": " << suggestDepartment() << "\n";
    }
};

class OutPatient : public Patient {
    double consultationFee;
public:
    OutPatient() : consultationFee(0.0) {}
    void input() {
        Patient::input();
        cout << "Enter consultation fee: ";
        while (true) {
            string s = readLineTrim();
            double v = parseDouble(s);
            if (v >= 0) { consultationFee = v; break; }
            cout << "Invalid amount.\n";
        }
        totalPaid = consultationFee;
    }
    void displayFull(int index) const {
        cout << "\n--- OUT-PATIENT RECORD #" << index+1 << " ---\n";
        displayBasicInfo();
        cout << left << setw(20) << "Consult Fee" << ": " << fixed << setprecision(2) << consultationFee << "\n";
        cout << left << setw(20) << "Department" << ": " << suggestDepartment() << "\n";
    }
};

// ---------- Staff / Employee ----------
class Staff : public Person {
protected:
    string staffID;
    string department;
    double basic;
    double hra;
    double da;
    double totalSalary;
    int lateDays;
    int yearsExp;
    bool added;
public:
    Staff() : basic(0.0), hra(0.0), da(0.0), totalSalary(0.0), lateDays(0), yearsExp(0), added(false) {}
    void input() {
        inputBasic();
        while (true) {
            cout << "Staff ID (digits only): ";
            string s = readLineTrim();
            if (isDigitsOnly(s)) { staffID = s; break; }
            cout << "Invalid ID.\n";
        }
        cout << "Department: ";
        department = readLineTrim();
        while (true) {
            cout << "Basic salary: ";
            string s = readLineTrim();
            double v = parseDouble(s);
            if (v >= 0) { basic = v; break; }
            cout << "Invalid amount.\n";
        }
        while (true) {
            cout << "HRA: ";
            string s = readLineTrim();
            double v = parseDouble(s);
            if (v >= 0) { hra = v; break; }
            cout << "Invalid amount.\n";
        }
        while (true) {
            cout << "DA: ";
            string s = readLineTrim();
            double v = parseDouble(s);
            if (v >= 0) { da = v; break; }
            cout << "Invalid amount.\n";
        }
        while (true) {
            cout << "Years of experience: ";
            string s = readLineTrim();
            if (isDigitsOnly(s)) { yearsExp = atoi(s.c_str()); break; }
            cout << "Invalid value.\n";
        }
        while (true) {
            cout << "Late days in month: ";
            string s = readLineTrim();
            if (isDigitsOnly(s)) { lateDays = atoi(s.c_str()); break; }
            cout << "Invalid value.\n";
        }
        totalSalary = basic + hra + da;
        added = true;
    }
    void calculateSalary() {
        if (!added) { cout << "No staff record.\n"; return; }
        totalSalary = basic + hra + da;
        cout << "Salary calculated: " << fixed << setprecision(2) << totalSalary << "\n";
    }
    void display() const {
        cout << "\n--- STAFF RECORD ---\n";
        displayBasic();
        cout << left << setw(16) << "Staff ID" << ": " << staffID << "\n";
        cout << left << setw(16) << "Dept" << ": " << department << "\n";
        cout << left << setw(16) << "Basic" << ": " << basic << "\n";
        cout << left << setw(16) << "HRA" << ": " << hra << "\n";
        cout << left << setw(16) << "DA" << ": " << da << "\n";
        cout << left << setw(16) << "Total Salary" << ": " << fixed << setprecision(2) << totalSalary << "\n";
        cout << left << setw(16) << "YearsExp" << ": " << yearsExp << "\n";
        cout << left << setw(16) << "LateDays" << ": " << lateDays << "\n";
    }
    void checkPromotion() const {
        if (yearsExp >= 2) cout << name << " is eligible for promotion.\n";
        else cout << name << " is not eligible for promotion.\n";
    }
    string getDepartment() const { return department; }
    double getTotalSalary() const { return totalSalary; }
};

// ---------- Hospital System (manager) ----------
class Hospital {
    vector<InPatient> inPatients;
    vector<OutPatient> outPatients;
    vector<Staff> staffMembers;
    double hospitalRevenue;
public:
    Hospital() : hospitalRevenue(0.0) {}

    void mainMenu() {
        while (true) {
            cout << "\n====== HOSPITAL MANAGEMENT SYSTEM ======\n";
            cout << "1. Register In-Patient\n";
            cout << "2. Register Out-Patient\n";
            cout << "3. Add Staff Member\n";
            cout << "4. Billing & Payments (summary)\n";
            cout << "5. Reports: Patients / Staff\n";
            cout << "6. Hospital Statistics\n";
            cout << "7. Compare two patients by spending\n";
            cout << "8. Revenue projection\n";
            cout << "9. Staff: calculate salary / promotion / list\n";
            cout << "0. Exit\n";
            cout << "Enter choice: ";
            string choice; getline(cin, choice);
            if (choice == "1") addInPatient();
            else if (choice == "2") addOutPatient();
            else if (choice == "3") addStaff();
            else if (choice == "4") billingMenu();
            else if (choice == "5") reportsMenu();
            else if (choice == "6") showStatistics();
            else if (choice == "7") comparePatients();
            else if (choice == "8") revenueProjection();
            else if (choice == "9") staffOperations();
            else if (choice == "0") { cout << "Exiting... Goodbye!\n"; break; }
            else cout << "Invalid choice.\n";
        }
    }

private:
    void addInPatient() {
        InPatient p;
        cout << "\n--- Registering In-Patient ---\n";
        p.input();
        inPatients.push_back(p);
        hospitalRevenue += p.getTotalPaid();
        cout << "In-patient registered successfully.\n";
        pause();
    }

    void addOutPatient() {
        OutPatient p;
        cout << "\n--- Registering Out-Patient ---\n";
        p.input();
        outPatients.push_back(p);
        hospitalRevenue += p.getTotalPaid();
        cout << "Out-patient registered successfully.\n";
        pause();
    }

    void addStaff() {
        Staff s;
        cout << "\n--- Add Staff Member ---\n";
        s.input();
        staffMembers.push_back(s);
        cout << "Staff added.\n";
        pause();
    }

    void billingMenu() {
        cout << "\n--- Billing & Payments Summary ---\n";
        cout << "Total in-patients: " << inPatients.size() << "\n";
        cout << "Total out-patients: " << outPatients.size() << "\n";
        cout << fixed << setprecision(2);
        cout << "Total hospital revenue so far: " << hospitalRevenue << "\n";
        
        vector<double> payments;
        for (vector<InPatient>::const_iterator it = inPatients.begin(); it != inPatients.end(); ++it) payments.push_back(it->getTotalPaid());
        for (vector<OutPatient>::const_iterator it = outPatients.begin(); it != outPatients.end(); ++it) payments.push_back(it->getTotalPaid());

        if (!payments.empty()) {
            vector<double>::iterator min_it = std::min_element(payments.begin(), payments.end());
            vector<double>::iterator max_it = std::max_element(payments.begin(), payments.end());
            cout << "Highest payment: " << *max_it << "\n";
            cout << "Lowest payment : " << *min_it << "\n";
        } else cout << "No payment data available.\n";
        pause();
    }

    void reportsMenu() {
        while (true) {
            cout << "\n--- Reports Menu ---\n";
            cout << "1. List all In-Patients\n";
            cout << "2. List all Out-Patients\n";
            cout << "3. Search patient by name\n";
            cout << "4. List all Staff\n";
            cout << "0. Back\n";
            cout << "Choice: ";
            string c = readLineTrim();
            if (c == "1") listInPatients();
            else if (c == "2") listOutPatients();
            else if (c == "3") searchPatient();
            else if (c == "4") listStaff();
            else if (c == "0") break;
            else cout << "Invalid choice.\n";
        }
    }

    void listInPatients() {
        if (inPatients.empty()) { cout << "No in-patients recorded.\n"; pause(); return; }
        for (size_t i = 0; i < inPatients.size(); ++i) inPatients[i].displayFull((int)i);
        pause();
    }

    void listOutPatients() {
        if (outPatients.empty()) { cout << "No out-patients recorded.\n"; pause(); return; }
        for (size_t i = 0; i < outPatients.size(); ++i) outPatients[i].displayFull((int)i);
        pause();
    }

    void listStaff() {
        if (staffMembers.empty()) { cout << "No staff recorded.\n"; pause(); return; }
        for (size_t i = 0; i < staffMembers.size(); ++i) {
            cout << "\n--- Staff #" << i+1 << " ---\n";
            staffMembers[i].display();
        }
        pause();
    }

    void searchPatient() {
        cout << "Enter name to search: ";
        string key = toLower(readLineTrim());
        bool found = false;
        for (size_t i = 0; i < inPatients.size(); ++i) {
            if (toLower(inPatients[i].getName()).find(key) != string::npos) {
                inPatients[i].displayFull((int)i);
                found = true;
            }
        }
        for (size_t i = 0; i < outPatients.size(); ++i) {
            if (toLower(outPatients[i].getName()).find(key) != string::npos) {
                outPatients[i].displayFull((int)i);
                found = true;
            }
        }
        if (!found) cout << "No patient matched.\n";
        pause();
    }

    void showStatistics() {
        cout << "\n--- Hospital Statistics ---\n";
        size_t totalPatients = inPatients.size() + outPatients.size();
        cout << "Total patients registered: " << totalPatients << "\n";
        cout << "In-patients: " << inPatients.size() << " | Out-patients: " << outPatients.size() << "\n";
        cout << fixed << setprecision(2);
        cout << "Total revenue: " << hospitalRevenue << "\n";
        if (totalPatients > 0) {
            cout << "Average revenue per patient: " << hospitalRevenue / totalPatients << "\n";
        }
        
        vector<double> payments;
        for (vector<InPatient>::const_iterator it = inPatients.begin(); it != inPatients.end(); ++it) payments.push_back(it->getTotalPaid());
        for (vector<OutPatient>::const_iterator it = outPatients.begin(); it != outPatients.end(); ++it) payments.push_back(it->getTotalPaid());

        if (!payments.empty()) {
            sort(payments.begin(), payments.end());
            double median = 0;
            size_t n = payments.size();
            if (n % 2 == 0) median = (payments[n/2 - 1] + payments[n/2]) / 2.0;
            else median = payments[n/2];
            cout << "Median payment: " << median << "\n";
        }
        pause();
    }

    void comparePatients() {
        if (inPatients.empty() && outPatients.empty()) { cout << "No patients available to compare.\n"; pause(); return; }
        cout << "List of patients (index + type):\n";
        vector<pair<string, double> > list;
        for (size_t i = 0; i < inPatients.size(); ++i) list.push_back(make_pair("IN:" + inPatients[i].getName(), inPatients[i].getTotalPaid()));
        for (size_t i = 0; i < outPatients.size(); ++i) list.push_back(make_pair("OUT:" + outPatients[i].getName(), outPatients[i].getTotalPaid()));
        
        for (size_t i = 0; i < list.size(); ++i) cout << i+1 << ". " << list[i].first << " (paid: " << list[i].second << ")\n";
        
        cout << "Choose two indexes to compare (e.g. 1 3): ";
        string line = readLineTrim();
        istringstream iss(line);
        int a, b; if (!(iss >> a >> b)) { cout << "Invalid input.\n"; pause(); return; }
        if (a < 1 || b < 1 || a > (int)list.size() || b > (int)list.size()) { cout << "Index out of range.\n"; pause(); return; }
        double pa = list[a-1].second, pb = list[b-1].second;
        if (pa == pb) cout << "Both spent the same: " << pa << "\n";
        else if (pa > pb) {
            cout << list[a-1].first << " spent " << pa - pb << " more than " << list[b-1].first << "\n";
            cout << "That's " << fixed << setprecision(1) << ((pa/pb - 1.0) * 100.0) << "% higher.\n";
        } else {
            cout << list[b-1].first << " spent " << pb - pa << " more than " << list[a-1].first << "\n";
            cout << "That's " << fixed << setprecision(1) << ((pb/pa - 1.0) * 100.0) << "% higher.\n";
        }
        pause();
    }

    void revenueProjection() {
        cout << "Project revenue for how many additional patients? ";
        string s = readLineTrim();
        if (!isDigitsOnly(s)) { cout << "Invalid number.\n"; pause(); return; }
        int future = atoi(s.c_str());
        size_t currentPatients = inPatients.size() + outPatients.size();
        if (currentPatients == 0) { cout << "No current data for projection.\n"; pause(); return; }
        double average = hospitalRevenue / currentPatients;
        double projected = average * future;
        cout << fixed << setprecision(2);
        cout << "Average revenue per patient: " << average << "\n";
        cout << "Projected additional revenue for " << future << " patients: " << projected << "\n";
        cout << "Total projected revenue: " << hospitalRevenue + projected << "\n";
        pause();
    }

    void staffOperations() {
        while (true) {
            cout << "\n--- Staff Operations ---\n";
            cout << "1. Calculate salary for staff #n\n";
            cout << "2. Check promotion eligibility for staff #n\n";
            cout << "3. List all staff\n";
            cout << "0. Back\n";
            cout << "Choice: ";
            string c = readLineTrim();
            if (c == "1") {
                if (staffMembers.empty()) { cout << "No staff.\n"; pause(); continue; }
                cout << "Enter staff index (1.." << staffMembers.size() << "): ";
                string s = readLineTrim();
                if (!isDigitsOnly(s)) { cout << "Invalid index.\n"; pause(); continue; }
                int idx = atoi(s.c_str());
                if (idx < 1 || idx > (int)staffMembers.size()) { cout << "Index out of range.\n"; pause(); continue; }
                staffMembers[idx-1].calculateSalary();
                pause();
            } else if (c == "2") {
                if (staffMembers.empty()) { cout << "No staff.\n"; pause(); continue; }
                cout << "Enter staff index (1.." << staffMembers.size() << "): ";
                string s = readLineTrim();
                if (!isDigitsOnly(s)) { cout << "Invalid index.\n"; pause(); continue; }
                int idx = atoi(s.c_str());
                if (idx < 1 || idx > (int)staffMembers.size()) { cout << "Index out of range.\n"; pause(); continue; }
                staffMembers[idx-1].checkPromotion();
                pause();
            } else if (c == "3") {
                listStaff();
            } else if (c == "0") break;
            else cout << "Invalid choice.\n";
        }
    }
};

// ---------- main ----------
int main() {
    Hospital hospital;
    hospital.mainMenu();
    return 0;
}


