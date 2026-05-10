#include "SFMLApp.h"
#include "FileNotFoundException.h"
#include <sstream>
#include <iomanip>

/*
(71,45,48) backgrounds,
dark (50,28,32) cards
(100,58,65) hover states
(226,109,92)
cream  primary text,
(180,190,140) secondary text.
*/

//Since string not allowed 
//functions to perform --> length calculuate, copy string, concatenate and compare . whether char is digit and int to char
//int to string and copying
int customStrLen(const char* string) {
    int len = 0;
    while (string[len] != '\0') {
        len++;
    }
    return len;
}

void StrCpyFunction(char* storeInto, const char* storingChar) {
    int i = 0;
    while (storingChar[i] != '\0') {
        storeInto[i] = storingChar[i];
        i++;
    }
    storeInto[i] = '\0';
}

void strcatFunction(char* storeInto, const char* storingChar) {
    int destLen = customStrLen(storeInto);
    int i = 0;
    while (storingChar[i] != '\0') {
        storeInto[destLen + i] = storingChar[i];
        i++;
    }
    storeInto[destLen + i] = '\0';
}

int customStrCmp(const char* str1, const char* str2) {
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i]) {
            return str1[i] - str2[i];
        }
        i++;
    }
    return str1[i] - str2[i];
}

bool customIsDigit(char c) {
    return (c >= '0' && c <= '9');
}

int customCharToInt(char c) {
    return c - '0';
}

int customStrToInt(const char* str) {
    int result = 0;
    int i = 0;
    while (str[i] != '\0' && customIsDigit(str[i])) {
        result = result * 10 + customCharToInt(str[i]);
        i++;
    }
    return result;
}

void intToStrFunction(int num, char* storingInto, int charSize) {
    if (num == 0) {
        storingInto[0] = '0';
        storingInto[1] = '\0';
        return;
    }

    char temp[20];
    int tempIndex = 0;
    int n = num;

    while (n > 0) {
        temp[tempIndex++] = '0' + (n % 10);
        n = n / 10;
    }

    int bufferIndex = 0;
    for (int i = tempIndex - 1; i >= 0 && bufferIndex < charSize - 1; i--) {
        storingInto[bufferIndex++] = temp[i];
    }
    storingInto[bufferIndex] = '\0';
}

void customDoubleToStr(double num, char* storingInto, int charSize) {
    int intPart = (int)num;
    double fracPart = num - intPart;

    char intStr[20];
    intToStrFunction(intPart, intStr, 20);
    StrCpyFunction(storingInto, intStr);

    int len = customStrLen(storingInto);
    if (len < charSize - 1) {
        storingInto[len] = '.';
        len++;

        for (int i = 0; i < 2; i++) {
            fracPart = fracPart * 10;
            int digit = (int)fracPart;
            if (len < charSize - 1) {
                storingInto[len++] = '0' + digit;
            }
            fracPart = fracPart - digit;
        }
        storingInto[len] = '\0';
    }
}

void copyString(char* copyInto, const char* tobeCopied, int maxLength) {
    int i = 0;
    for (int index = 0; index < maxLength && tobeCopied[index] != '\0'; index++) {
        copyInto[index] = tobeCopied[index];
        i++;
    }
    copyInto[i] = '\0';
}

//Constructor 
SFMLApp::SFMLApp()
    : window(sf::VideoMode(1000, 800), "MediCore Hospital Management System"),
    currentScreen(Screen::MAIN_MENU),
    loggedPatient(nullptr), loggedDoctor(nullptr), loggedAdmin(nullptr),
    loginFailCount(0), inputString(""), statusMessage(""), displayBuffer(""),
    menuSelection(0), inputActive(true), inputStep(0),
    bookDoctorIndex(-1), isPasswordField(false)
{
    window.setFramerateLimit(60);
    if (!font.loadFromFile("arial.ttf")) {
        font.loadFromFile("C:/Windows/Fonts/arial.ttf");
    }
    loadAllData();
}


//basically saara load karnai kai liyai use
void SFMLApp::loadAllData() {
    patients.clearAllData();
    doctors.clearAllData();
    admins.clearAllData();
    appointments.clearAllData();
    bills.clearAllData();
    prescriptions.clearAllData();
    try { FileHandler::loadPatients(patients); }
    catch (FileNotFoundException&) {}
    try { FileHandler::loadDoctors(doctors); }
    catch (FileNotFoundException&) {}
    try { FileHandler::loadAdmins(admins); }
    catch (FileNotFoundException&) {}
    try { FileHandler::loadAppointments(appointments); }
    catch (FileNotFoundException&) {}
    try { FileHandler::loadBills(bills); }
    catch (FileNotFoundException&) {}
    try { FileHandler::loadPrescriptions(prescriptions); }
    catch (FileNotFoundException&) {}

}

//Reloading all data
void SFMLApp::reloadAllData() {
    loadAllData();
}

void SFMLApp::copyToStore(char* placeToStore, const char* toStore, int maxLen) {
    int i = 0;
    for (; i < maxLen - 1 && toStore[i] != '\0'; i++) {
        placeToStore[i] = toStore[i];
    }
    placeToStore[i] = '\0';
}

//checking if string equal --> case sensitve --> best use hamain password
bool SFMLApp::stringEqual(const char* string1, const char* string2) const {
    int i = 0;
    while (string1[i] != '\0' && string2[i] != '\0') {
        if (string1[i] != string2[i]) {
            return false;
        }
        i++;
    }
    return string1[i] == '\0' && string2[i] == '\0';
}

//Ensuring strings check but without need of case
bool SFMLApp::stringEqualCase(const char* string1, const char* string2) const {
    int i = 0;
    while (string1[i] != '\0' && string2[i] != '\0') {
        char character1;
        char character2;
        if (string1[i] >= 'A' && string1[i] <= 'Z') {
            character1 = string1[i] + 32;
        }
        else {
            character1 = string1[i];
        }
        if (string2[i] >= 'A' && string2[i] <= 'Z')
        {
            character2 = string2[i] + 32;
        }
        else {
            character2 = string2[i];
        }
        if (character1 != character2) {
            return false;
        }
        i++;
    }
    if (string1[i] == '\0' && string2[i] == '\0') {
        return true;
    }
    else {
        return false;
    }
}


void SFMLApp::getTodayDate(char* date) {
    time_t now = time(nullptr); //current time
    //converting time into like a readable format jo hamain chahiyai day , month , year
    tm tmInfo;
    localtime_s(&tmInfo, &now);
    strftime(date, 11, "%d-%m-%Y", &tmInfo);
}

//patient id lena and then searching unpaid
int SFMLApp::countUnpaidBills(int patientID) {
    int count = 0;
    for (int i = 0; i < bills.arraySize(); i++) {
        Bill& bill = bills.getAll()[i];
        if (bill.getPatientID() == patientID && stringEqual(bill.getStatus(), "unpaid")) {
            count++;
        }
    }
    return count;
}

bool SFMLApp::dateIsOverdue(const char* date) {
    int day = (date[0] - '0') * 10 + (date[1] - '0');
    int month = (date[3] - '0') * 10 + (date[4] - '0');
    int year = (date[6] - '0') * 1000 + (date[7] - '0') * 100
        + (date[8] - '0') * 10 + (date[9] - '0');
    //Main goal converting into like time we can compare i.e seconds
    //agar 7 days sai more tou overdue
    tm t = {};
    t.tm_mday = day;
    t.tm_mon = month - 1;
    t.tm_year = year - 1900;
    time_t billTime = mktime(&t);
    time_t now = time(nullptr);
    return difftime(now, billTime) > 7 * 24 * 3600;
}

int SFMLApp::buildAvailableSlots(int doctorID, const char* date, char available[][6]) {
    const char* allSlots[8] = { "09:00","10:00","11:00","12:00","13:00","14:00","15:00","16:00" };
    int count = 0;
    for (int s = 0; s < 8; s++) {
        bool taken = false;
        for (int i = 0; i < appointments.arraySize(); i++) {
            Appointment& ap = appointments.getAll()[i];
            //agar doctor same , date same , slot same and status is cancelled --> then we make it taken
            if (ap.getDoctorID() == doctorID &&
                stringEqual(ap.getDate(), date) &&
                stringEqual(ap.getTimeSlot(), allSlots[s]) &&
                !stringEqual(ap.getStatus(), "cancelled")) {
                taken = true;
                break;
            }
        }
        //return no. of slots not taken
        if (!taken) {
            copyString(available[count], allSlots[s], 6);
            count++;
        }
    }
    return count;
}

void SFMLApp::sortAppointmentsByDate(Appointment* array, int size, bool ascending) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            const char* date1 = array[j].getDate();
            const char* date2 = array[j + 1].getDate();
            int date1Integer = ((date1[6] - '0') * 1000 + (date1[7] - '0') * 100 + (date1[8] - '0') * 10 + (date1[9] - '0')) * 10000
                + ((date1[3] - '0') * 10 + (date1[4] - '0')) * 100
                + (date1[0] - '0') * 10 + (date1[1] - '0');
            int date2Integer = ((date2[6] - '0') * 1000 + (date2[7] - '0') * 100 + (date2[8] - '0') * 10 + (date2[9] - '0')) * 10000
                + ((date2[3] - '0') * 10 + (date2[4] - '0')) * 100
                + (date2[0] - '0') * 10 + (date2[1] - '0');
            bool shouldSwap;
            if (ascending) {
                shouldSwap = (date1Integer > date2Integer);
            }
            else {
                shouldSwap = (date1Integer < date2Integer);
            }
            if (shouldSwap) {
                Appointment temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

//SAME LOGIC AS SORT APPOINTMENT -->BUBBLE SWAP AND CONVERSION TO INT FORM
void SFMLApp::sortPrescriptionsByDate(Prescription* array, int size, bool descending) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            const char* date1 = array[j].getDate();
            const char* date2 = array[j + 1].getDate();
            int date1Integer = ((date1[6] - '0') * 1000 + (date1[7] - '0') * 100 + (date1[8] - '0') * 10 + (date1[9] - '0')) * 10000
                + ((date1[3] - '0') * 10 + (date1[4] - '0')) * 100
                + (date1[0] - '0') * 10 + (date1[1] - '0');
            int date2Integer = ((date2[6] - '0') * 1000 + (date2[7] - '0') * 100 + (date2[8] - '0') * 10 + (date2[9] - '0')) * 10000
                + ((date2[3] - '0') * 10 + (date2[4] - '0')) * 100
                + (date2[0] - '0') * 10 + (date2[1] - '0');
            bool shouldSwap;
            if (descending) {
                shouldSwap = (date1Integer > date2Integer);
            }
            else {
                shouldSwap = (date1Integer < date2Integer);
            }

            if (shouldSwap) {
                Prescription temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

//basically --> patient ki id and if password is pass --> phir patient found
//getall() will give pointer soooo phir we can access and search
//wahi logic lagai doctor and admin kai liyai
Patient* SFMLApp::findPatientByCredentials(int id, const char* pass) {
    for (int i = 0; i < patients.arraySize(); i++) {
        Patient& object = patients.getAll()[i];
        if (object.getPatientID() == id && stringEqual(object.getPassword(), pass)) {
            return &object;
        }
    }
    return nullptr;
}

Doctor* SFMLApp::findDoctorByCredentials(int id, const char* pass) {
    for (int i = 0; i < doctors.arraySize(); i++) {
        Doctor& d = doctors.getAll()[i];
        if (d.getDoctorID() == id && stringEqual(d.getPassword(), pass)) {
            return &d;
        }
    }
    return nullptr;
}

Admin* SFMLApp::findAdminByCredentials(int id, const char* pass) {
    for (int i = 0; i < admins.arraySize(); i++) {
        Admin& a = admins.getAll()[i];
        if (a.getAdminID() == id && stringEqual(a.getPassword(), pass)) {
            return &a;
        }
    }
    return nullptr;
}

//Basically takes test and renders on to the screen
void SFMLApp::drawText(const char* text, float x, float y, unsigned int size, sf::Color color) {
    sf::Text t; //SFML object for rendering
    t.setFont(font);
    t.setString(text); //sfml text mai convert
    t.setCharacterSize(size);
    t.setFillColor(color);
    t.setPosition(x, y);
    window.draw(t); //draw command to make it work on screen
}

void SFMLApp::drawWrappedText(const char* text, float x, float y, float maxWidth, unsigned int size, sf::Color color) {
    sf::Text measure;
    measure.setFont(font);
    measure.setCharacterSize(size);
    char line[2000] = "";
    char word[1000] = "";
    float lineY = y; // y position where to add
    int i = 0;

    while (text[i] != '\0') {
        //if new line ham draw karain gain
        // line ko dubara 0 and move to the enxt
        if (text[i] == '\n') {
            if (customStrLen(word) > 0) {
                strcatFunction(line, word);
                word[0] = '\0';
            }
            drawText(line, x, lineY, size, color);
            line[0] = '\0';
            lineY += size + 4;
            i++;
        }

      
        else if (text[i] == ' ') {
            char test[2000];
            StrCpyFunction(test, line);
            strcatFunction(test, word);
            strcatFunction(test, " ");
            measure.setString(test);
            if (measure.getLocalBounds().width > maxWidth && customStrLen(line) > 0) {
                drawText(line, x, lineY, size, color); // draw current line
                //phir copy the word into the new line and then we go ahead
                StrCpyFunction(line, word);
                strcatFunction(line, " ");
                lineY += size + 4;
            }
            else {
                StrCpyFunction(line, test);
            }
            word[0] = '\0';
            i++;
        }
        else {
            //add the character to the word
            int len = customStrLen(word);
            word[len] = text[i];
            word[len + 1] = '\0';
            i++;
        }
    }
    if (customStrLen(word) > 0) {
        strcatFunction(line, word);
    }
    if (customStrLen(line) > 0) {
        drawText(line, x, lineY, size, color);
    }
}


void SFMLApp::drawPanel(float x, float y, float width, float height, sf::Color color) {
    //sf:: shape name(position)

    sf::RectangleShape rect(sf::Vector2f(width, height));
    rect.setPosition(x, y);
    rect.setFillColor(color);
    rect.setOutlineThickness(0);
    window.draw(rect);
}

void SFMLApp::drawButton(const char* label, float x, float y, float w, float h, bool highlighted) {
    sf::Color fill;
    if (highlighted) {
        fill = sf::Color(226, 109, 92);
    }
    else {
        fill = sf::Color(100, 58, 65);
    }

    sf::Color textCol;
    if (highlighted) {
        textCol = sf::Color(50, 28, 32);
    }
    else {
        textCol = sf::Color(255, 225, 168);
    }

    sf::RectangleShape body(sf::Vector2f(w - h, h));
    body.setPosition(x, y);
    body.setFillColor(fill);
    window.draw(body);

    drawText(label, x, y, 16, textCol);
}

void SFMLApp::drawInputBox(const char* label, float x, float y, float w, bool active) {
    //Drawing user ID or password label basically box sai uper rukhnai kai liyai
    drawText(label, x, y - 20, 14, sf::Color(180, 190, 140));

    //main box jahan hamara tpe hona
    sf::RectangleShape box(sf::Vector2f(w, 36));
    box.setPosition(x, y);
    box.setFillColor(sf::Color(50, 28, 32));
    window.draw(box);

    //waisai border daalnai kai liyai
    sf::RectangleShape border(sf::Vector2f(w, 3));
    border.setPosition(x, y + 33);
    sf::Color borderColor;
    if (active) {
        borderColor = sf::Color(226, 109, 92);
    }
    else {
        borderColor = sf::Color(100, 58, 65);
    }
    border.setFillColor(borderColor);
    window.draw(border);

    char display[1000];
    //agar password we will use * 
    if (isPasswordField) {
        int len = customStrLen(inputString);
        for (int i = 0; i < len && i < 999; i++) {
            display[i] = '*';
        }
        display[len] = '\0';
    }
    else {
        StrCpyFunction(display, inputString);
    }
    //cursor dalnai kai liyai
    if (active) {
        int len = customStrLen(display);
        display[len] = '|';
        display[len + 1] = '\0';
    }
    drawText(display, x + 10, y + 8, 16, sf::Color(255, 225, 168));
}

void SFMLApp::drawMainMenu() {
    //clear first anything
    window.clear(sf::Color(71, 45, 48));
    //rectangle of the size of window a bar uper
    sf::RectangleShape topBar(sf::Vector2f(1000, 70));
    topBar.setPosition(0, 0);
    topBar.setFillColor(sf::Color(50, 28, 32));
    window.draw(topBar);

    //Contrast
    sf::RectangleShape lowBar(sf::Vector2f(1000, 30));
    lowBar.setPosition(0, 70);
    lowBar.setFillColor(sf::Color(226, 109, 92));
    window.draw(lowBar);

    //Centerised one below the other
    drawText("MEDICORE", 400, 16, 30, sf::Color(255, 225, 168));
    drawText("Hospital Management System", 370, 50, 16, sf::Color(180, 190, 140));


    drawText("Select Role", 30, 100, 26, sf::Color(255, 225, 168));
    drawText("Arrow keys + Enter", 30, 136, 13, sf::Color(180, 190, 140));

    //Basically line before the options
    sf::RectangleShape headDiv(sf::Vector2f(940, 2));
    headDiv.setPosition(30, 158);
    headDiv.setFillColor(sf::Color(100, 58, 65));
    window.draw(headDiv);

    const char* labels[4] = { "Patient Login",  "Doctor Login",  "Admin Login",  "Exit" };
    const char* sublabels[4] = { "Appointments & records",
                                  "Schedule & prescriptions",
                                  "System administration",
                                  "Close application" };

    for (int i = 0; i < 4; i++) {
        float boxX = 30;
        float boxY = 170 + i * 140;
        //Basically for menu selection we created taakai 4 cards/boxes banain
        //bool wala if card selected --> for changing colours
        bool  selected = (menuSelection == i);

        //Drawing the box
        sf::RectangleShape card(sf::Vector2f(940, 124));
        card.setPosition(boxX, boxY);
        if (selected) {
            card.setFillColor(sf::Color(100, 58, 65));
        }
        else {
            card.setFillColor(sf::Color(55, 32, 36));
        }
        window.draw(card);

        //Agar selected sath aik strip bhi
        sf::RectangleShape stripe(sf::Vector2f(5, 124));
        stripe.setPosition(boxX, boxY);
        if (selected) {
            stripe.setFillColor(sf::Color(226, 109, 92));
        }
        else {
            stripe.setFillColor(sf::Color(71, 45, 48));
        }
        window.draw(stripe);


        char num[10];
        // custom int to string conversion
        int tempNum = i + 1;
        int numIdx = 0;
        if (tempNum == 0) {
            num[numIdx++] = '0';
        }
        else {
            char revNum[10];
            int revIdx = 0;
            while (tempNum > 0) {
                revNum[revIdx++] = '0' + (tempNum % 10);
                tempNum /= 10;
            }
            for (int k = revIdx - 1; k >= 0; k--) {
                num[numIdx++] = revNum[k];
            }
        }
        num[numIdx] = '\0';
        strcatFunction(num, ".");

        //circle ka index: sf::circle name(radius)
        sf::CircleShape circle(20);
        circle.setPosition(boxX + 6, boxY + 27);
        circle.setFillColor(sf::Color(71, 45, 48));
        window.draw(circle);

        if (selected) {
            drawText(num, boxX + 18, boxY + 38, 18, sf::Color(226, 109, 92));
        }
        else {
            drawText(num, boxX + 18, boxY + 38, 18, sf::Color(100, 58, 65));
        }
        if (selected) {
            drawText(labels[i], boxX + 52, boxY + 28, 22, sf::Color(255, 225, 168));
        }
        else {
            drawText(labels[i], boxX + 52, boxY + 28, 22, sf::Color(180, 190, 140));
        }
        if (selected) {
            drawText(sublabels[i], boxX + 52, boxY + 62, 13, sf::Color(226, 109, 92));
        }
        else {
            drawText(sublabels[i], boxX + 52, boxY + 62, 13, sf::Color(100, 58, 65));
        }
    }

    if (customStrLen(statusMessage) > 0) {
        drawText(statusMessage, 30, 768, 13, sf::Color(226, 109, 92));
    }
}

void SFMLApp::drawLoginScreen(const char* title) {
    //Basically what this does is 
    //make rectangles for UI, based on status determines whether id entered or not etc
    // then after that it(only if patient)it also gives option to register(write in patient file ho ga)
    window.clear(sf::Color(71, 45, 48));

    sf::RectangleShape topBar(sf::Vector2f(1000, 70));
    topBar.setPosition(0, 0);
    topBar.setFillColor(sf::Color(50, 28, 32));
    window.draw(topBar);

    sf::RectangleShape topLine(sf::Vector2f(1000, 4));
    topLine.setPosition(0, 70);
    topLine.setFillColor(sf::Color(226, 109, 92));
    window.draw(topLine);
    drawText("MEDICORE", 30, 16, 30, sf::Color(255, 225, 168));

    sf::RectangleShape card(sf::Vector2f(540, 480));
    card.setPosition(230, 110);
    card.setFillColor(sf::Color(50, 28, 32));
    window.draw(card);

    sf::RectangleShape cardTop(sf::Vector2f(540, 4));
    cardTop.setPosition(230, 110);
    cardTop.setFillColor(sf::Color(226, 109, 92));
    window.draw(cardTop);

    drawText(title, 260, 132, 26, sf::Color(255, 225, 168));
    drawText("Enter your credentials", 260, 168, 13, sf::Color(180, 190, 140));

    sf::RectangleShape div(sf::Vector2f(480, 1));
    div.setPosition(260, 192);
    div.setFillColor(sf::Color(100, 58, 65));
    window.draw(div);

    if (inputStep == 0) {
        drawInputBox("User ID", 260, 222, 480, true);
        drawInputBox("Password", 260, 316, 480, false);
    }
    else {
        sf::RectangleShape lockedBox(sf::Vector2f(480, 36));
        lockedBox.setPosition(260, 222);
        lockedBox.setFillColor(sf::Color(71, 45, 48));
        window.draw(lockedBox);

        sf::RectangleShape lockedBorder(sf::Vector2f(480, 3));
        lockedBorder.setPosition(260, 255);
        lockedBorder.setFillColor(sf::Color(100, 58, 65));
        window.draw(lockedBorder);

        char idDisplay[200];
        StrCpyFunction(idDisplay, "ID  ");
        strcatFunction(idDisplay, enteredIDDisplay);
        drawText(idDisplay, 270, 230, 15, sf::Color(180, 190, 140));
        drawInputBox("Password", 260, 316, 480, true);
    }

    drawButton("CONFIRM (click enter)", 260, 416, 480, 44, true);
    drawText("ESC = Back", 260, 474, 13, sf::Color(100, 58, 65));

    if (customStrLen(statusMessage) > 0) {
        drawText(statusMessage, 260, 500, 13, sf::Color(226, 109, 92));
    }
    
    bool isPatientLogin = false;
    for (int i = 0; title[i] != '\0'; i++) {
        if (title[i] == 'P' && title[i + 1] == 'a' && title[i + 2] == 't' &&
            title[i + 3] == 'i' && title[i + 4] == 'e' && title[i + 5] == 'n' && title[i + 6] == 't') {
            isPatientLogin = true;
            break;
        }
    }
    if (isPatientLogin) {
        drawText("No account? Press R to Register", 260, 548, 13, sf::Color(180, 190, 140));
    }
}
//drawing of patient, doctor , admin similar but labels different
void SFMLApp::drawPatientMenu() {
    window.clear(sf::Color(71, 45, 48));
    if (!loggedPatient) return;


    sf::RectangleShape header(sf::Vector2f(1000, 70));
    header.setPosition(0, 0);
    header.setFillColor(sf::Color(50, 28, 32));
    window.draw(header);
    sf::RectangleShape headerLine(sf::Vector2f(1000, 4));
    headerLine.setPosition(0, 70);
    headerLine.setFillColor(sf::Color(226, 109, 92));
    window.draw(headerLine);

    drawText("MEDICORE", 30, 16, 30, sf::Color(255, 225, 168));

    char welcome[200];
    StrCpyFunction(welcome, "Welcome, ");
    strcatFunction(welcome, loggedPatient->getName());
    drawText(welcome, 500, 14, 16, sf::Color(255, 225, 168));

    char balanceText[200];
    StrCpyFunction(balanceText, "Balance: PKR ");
    char balanceNum[50];
    customDoubleToStr(loggedPatient->getBalance(), balanceNum, 50);
    strcatFunction(balanceText, balanceNum);
    drawText(balanceText, 500, 42, 13, sf::Color(180, 190, 140));

    const char* options[8] = {
        "Book Appointment", "Cancel Appointment", "View My Appointments",
        "View Medical Records", "View My Bills", "Pay Bill",
        "Top Up Balance", "Logout"
    };
    //8 boxes soooo 8 loop
    for (int i = 0; i < 8; i++) {
        float boxX;
        if (i < 4) {
            boxX = 30;
        }
        else {
            boxX = 530;
        }
        float boxY = 90 + (i % 4) * 174;
        //is the current menu selected
        bool  sel = (menuSelection == i);

        sf::RectangleShape card(sf::Vector2f(460, 150));
        card.setPosition(boxX, boxY);
        if (sel) {
            card.setFillColor(sf::Color(100, 58, 65));
        }
        else {
            card.setFillColor(sf::Color(55, 32, 36));
        }
        window.draw(card);

        sf::RectangleShape stripe(sf::Vector2f(5, 150));
        stripe.setPosition(boxX, boxY);
        if (sel) {
            stripe.setFillColor(sf::Color(226, 109, 92));
        }
        else {
            stripe.setFillColor(sf::Color(71, 45, 48));
        }
        window.draw(stripe);

        char num[10];
        int tempNum = i + 1;
        int numIdx = 0;
        if (tempNum == 0) {
            num[numIdx++] = '0';
        }
        else {
            char revNum[10];
            int revIdx = 0;
            while (tempNum > 0) {
                revNum[revIdx++] = '0' + (tempNum % 10);
                tempNum /= 10;
            }
            for (int k = revIdx - 1; k >= 0; k--) {
                num[numIdx++] = revNum[k];
            }
        }
        num[numIdx] = '\0';
        strcatFunction(num, ".");

        if (sel) {
            drawText(num, boxX + 18, boxY + 56, 16, sf::Color(226, 109, 92));
        }
        else {
            drawText(num, boxX + 18, boxY + 56, 16, sf::Color(100, 58, 65));
        }
        if (sel) {
            drawText(options[i], boxX + 50, boxY + 56, 17, sf::Color(255, 225, 168));
        }
        else {
            drawText(options[i], boxX + 50, boxY + 56, 17, sf::Color(180, 190, 140));
        }
    }

    if (customStrLen(statusMessage) > 0) {
        drawText(statusMessage, 30, 784, 13, sf::Color(226, 109, 92));
    }
}

//same logic and design as patient bus cards/boxes ka faraq
void SFMLApp::drawDoctorMenu() {
    window.clear(sf::Color(71, 45, 48));
    if (!loggedDoctor) return;

    sf::RectangleShape header(sf::Vector2f(1000, 70));
    header.setPosition(0, 0);
    header.setFillColor(sf::Color(50, 28, 32));
    window.draw(header);

    sf::RectangleShape headerLine(sf::Vector2f(1000, 4));
    headerLine.setPosition(0, 70);
    headerLine.setFillColor(sf::Color(226, 109, 92));
    window.draw(headerLine);

    drawText("MEDICORE", 30, 16, 30, sf::Color(255, 225, 168));

    char hdr[200];
    StrCpyFunction(hdr, "Dr. ");
    strcatFunction(hdr, loggedDoctor->getName());
    strcatFunction(hdr, "  |  ");
    strcatFunction(hdr, loggedDoctor->getSpecialization());
    drawText(hdr, 500, 22, 15, sf::Color(180, 190, 140));

    const char* options[6] = {
        "View Today's Appointments", "Mark Appointment Complete",
        "Mark Appointment No-Show",  "Write Prescription",
        "View Patient Medical History", "Logout"
    };

    for (int i = 0; i < 6; i++) {
        float boxX = 30;
        float boxY = 90 + i * 118;
        bool  sel = (menuSelection == i);

        sf::RectangleShape card(sf::Vector2f(940, 100));
        card.setPosition(boxX, boxY);
        card.setPosition(boxX, boxY);
        if (sel) {
            card.setFillColor(sf::Color(100, 58, 65));
        }
        else {
            card.setFillColor(sf::Color(55, 32, 36));
        }
        window.draw(card);

        sf::RectangleShape stripe(sf::Vector2f(5, 100));
        stripe.setPosition(boxX, boxY);
        if (sel) {
            stripe.setFillColor(sf::Color(226, 109, 92));
        }
        else {
            stripe.setFillColor(sf::Color(71, 45, 48));
        }
        window.draw(stripe);

        char num[10];
        int tempNum = i + 1;
        int numIdx = 0;
        if (tempNum == 0) {
            num[numIdx++] = '0';
        }
        else {
            char revNum[10];
            int revIdx = 0;
            while (tempNum > 0) {
                revNum[revIdx++] = '0' + (tempNum % 10);
                tempNum /= 10;
            }
            for (int k = revIdx - 1; k >= 0; k--) {
                num[numIdx++] = revNum[k];
            }
        }
        num[numIdx] = '\0';
        strcatFunction(num, ".");

        if (sel) {
            drawText(num, boxX + 18, boxY + 56, 16, sf::Color(226, 109, 92));
        }
        else {
            drawText(num, boxX + 18, boxY + 56, 16, sf::Color(100, 58, 65));
        }
        if (sel) {
            drawText(options[i], boxX + 50, boxY + 56, 17, sf::Color(255, 225, 168));
        }
        else {
            drawText(options[i], boxX + 50, boxY + 56, 17, sf::Color(180, 190, 140));
        }
    }

    if (customStrLen(statusMessage) > 0) {
        drawText(statusMessage, 30, 800, 13, sf::Color(226, 109, 92));
    }
}

void SFMLApp::drawAdminMenu() {
    window.clear(sf::Color(71, 45, 48));

    sf::RectangleShape header(sf::Vector2f(1000, 70));
    header.setPosition(0, 0);
    header.setFillColor(sf::Color(50, 28, 32));
    window.draw(header);
    sf::RectangleShape headerLine(sf::Vector2f(1000, 4));
    headerLine.setPosition(0, 70);
    headerLine.setFillColor(sf::Color(226, 109, 92));
    window.draw(headerLine);

    drawText("MEDICORE", 30, 16, 30, sf::Color(255, 225, 168));
    drawText("Admin Panel", 500, 22, 16, sf::Color(180, 190, 140));

    const char* options[12] = {
    "Add Doctor",          "Remove Doctor",       "Add Patient",
    "Remove Patient",      "View All Patients",   "View All Doctors",
    "View All Appointments","View Unpaid Bills",  "Discharge Patient",
    "View Security Log",   "Generate Daily Report","Logout"
    };

    for (int i = 0; i < 12; i++) {
        float boxX;
        if (i < 6) {
            boxX = 30;
        }
        else {
            boxX = 530;
        }
        float boxY = 86 + (i % 6) * 118;
        bool  sel = (menuSelection == i);

        sf::RectangleShape card(sf::Vector2f(460, 100));
        card.setPosition(boxX, boxY);
        card.setPosition(boxX, boxY);
        if (sel) {
            card.setFillColor(sf::Color(100, 58, 65));
        }
        else {
            card.setFillColor(sf::Color(55, 32, 36));
        }
        window.draw(card);

        sf::RectangleShape stripe(sf::Vector2f(5, 100));
        stripe.setPosition(boxX, boxY);
        if (sel) {
            stripe.setFillColor(sf::Color(226, 109, 92));
        }
        else {
            stripe.setFillColor(sf::Color(71, 45, 48));
        };
        window.draw(stripe);

        char num[10];
        int tempNum = i + 1;
        int numberIndex = 0;
        if (tempNum == 0) {
            num[numberIndex++] = '0';
        }
        else {
            char reverseNumber[10];
            int reverseIndex = 0;
            while (tempNum > 0) {
                reverseNumber[reverseIndex++] = '0' + (tempNum % 10);
                tempNum /= 10;
            }
            for (int k = reverseIndex - 1; k >= 0; k--) {
                num[numberIndex++] = reverseNumber[k];
            }
        }
        num[numberIndex] = '\0';
        strcatFunction(num, ".");

        if (sel) {
            drawText(num, boxX + 18, boxY + 56, 16, sf::Color(226, 109, 92));
        }
        else {
            drawText(num, boxX + 18, boxY + 56, 16, sf::Color(100, 58, 65));
        }
        if (sel) {
            drawText(options[i], boxX + 50, boxY + 56, 17, sf::Color(255, 225, 168));
        }
        else {
            drawText(options[i], boxX + 50, boxY + 56, 17, sf::Color(180, 190, 140));
        }
    }

    if (customStrLen(statusMessage) > 0) {
        drawText(statusMessage, 30, 784, 13, sf::Color(226, 109, 92));
    }
}

//okkk bill , report , prescription
//tenon ka generic aik hi design
void SFMLApp::drawOutputScreen(const char* title) {
    window.clear(sf::Color(71, 45, 48));

    sf::RectangleShape header(sf::Vector2f(1000, 70));
    header.setPosition(0, 0);
    header.setFillColor(sf::Color(50, 28, 32));
    window.draw(header);

    sf::RectangleShape headerLine(sf::Vector2f(1000, 4));
    headerLine.setPosition(0, 70);
    headerLine.setFillColor(sf::Color(226, 109, 92));
    window.draw(headerLine);

    drawText("MEDICORE", 30, 16, 30, sf::Color(255, 225, 168));
    drawText(title, 500, 14, 18, sf::Color(180, 190, 140));
    drawText("ESC to go back", 500, 44, 13, sf::Color(100, 58, 65));

    sf::RectangleShape content(sf::Vector2f(940, 690));
    content.setPosition(30, 86);
    content.setFillColor(sf::Color(55, 32, 36));
    window.draw(content);

    sf::RectangleShape cstripe(sf::Vector2f(4, 690));
    cstripe.setPosition(30, 86);
    cstripe.setFillColor(sf::Color(226, 109, 92));
    window.draw(cstripe);

    drawWrappedText(displayBuffer, 46, 96, 900, 15, sf::Color(255, 225, 168));

    if (customStrLen(statusMessage) > 0) {
        drawText(statusMessage, 46, 784, 13, sf::Color(226, 109, 92));
    }
}

void SFMLApp::drawInputScreen(const char* title, const char* prompt) {
    window.clear(sf::Color(71, 45, 48));

    sf::RectangleShape header(sf::Vector2f(1000, 70));
    header.setPosition(0, 0);
    header.setFillColor(sf::Color(50, 28, 32));
    window.draw(header);
    sf::RectangleShape headerLine(sf::Vector2f(1000, 4));
    headerLine.setPosition(0, 70);
    headerLine.setFillColor(sf::Color(226, 109, 92));
    window.draw(headerLine);

    drawText("MEDICORE", 30, 16, 30, sf::Color(255, 225, 168));
    drawText(title, 500, 14, 18, sf::Color(180, 190, 140));
    drawText("ESC to cancel", 500, 44, 13, sf::Color(100, 58, 65));

    sf::RectangleShape card(sf::Vector2f(940, 560));
    card.setPosition(30, 86);
    card.setFillColor(sf::Color(55, 32, 36));
    window.draw(card);

    sf::RectangleShape bStripe(sf::Vector2f(4, 560));
    bStripe.setPosition(30, 86);
    bStripe.setFillColor(sf::Color(226, 109, 92));
    window.draw(bStripe);

    drawWrappedText(displayBuffer, 46, 96, 900, 14, sf::Color(255, 225, 168));
    drawInputBox(prompt, 46, 570, 900, true);

    if (customStrLen(statusMessage) > 0) {
        drawText(statusMessage, 46, 626, 13, sf::Color(226, 109, 92));
    }
}

//Register patient --> 6 steps --> 6 different panels we will use
//Up the same rectangles

void SFMLApp::drawRegisterPatient() {
    window.clear(sf::Color(71, 45, 48));

    sf::RectangleShape header(sf::Vector2f(1000, 70));
    header.setPosition(0, 0);
    header.setFillColor(sf::Color(50, 28, 32));
    window.draw(header);

    sf::RectangleShape headerLine(sf::Vector2f(1000, 4));
    headerLine.setPosition(0, 70);
    headerLine.setFillColor(sf::Color(226, 109, 92));
    window.draw(headerLine);

    drawText("MEDICORE", 30, 16, 30, sf::Color(255, 225, 168));
    drawText("Register New Patient", 500, 14, 18, sf::Color(180, 190, 140));
    drawText("ESC to cancel", 500, 44, 13, sf::Color(100, 58, 65));

    char stepText[50];
    StrCpyFunction(stepText, "Step ");
    char stepNum[10];
    intToStrFunction(inputStep + 1, stepNum, 10);
    strcatFunction(stepText, stepNum);
    strcatFunction(stepText, " / 6");
    drawText(stepText, 860, 22, 14, sf::Color(226, 109, 92));

    sf::RectangleShape card(sf::Vector2f(700, 560));
    card.setPosition(150, 86);
    card.setFillColor(sf::Color(55, 32, 36));
    window.draw(card);

    sf::RectangleShape bStripe(sf::Vector2f(4, 560));
    bStripe.setPosition(150, 86);
    bStripe.setFillColor(sf::Color(226, 109, 92));
    window.draw(bStripe);

    drawWrappedText(displayBuffer, 166, 96, 660, 14, sf::Color(255, 225, 168));

    const char* prompt = "";
    if (inputStep == 0) {
        prompt = "Full Name (max 50 chars)"; isPasswordField = false;
    }
    else if (inputStep == 1) {
        prompt = "Age";
    }
    else if (inputStep == 2) {
        prompt = "Gender (M/F)";
    }
    else if (inputStep == 3) {
        prompt = "Contact (11 digits)";
    }
    else if (inputStep == 4) {
        prompt = "Password (min 6 chars)";
        isPasswordField = true;
    }
    else if (inputStep == 5) {
        prompt = "Initial Balance (PKR)";
        isPasswordField = false;
    }

    drawInputBox(prompt, 166, 570, 660, true);

    if (customStrLen(statusMessage) > 0) {
        drawText(statusMessage, 166, 626, 13, sf::Color(226, 109, 92));
    }
}

void SFMLApp::run() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (currentScreen == Screen::MAIN_MENU) {
                handleMainMenu(event);
            }
            else if (currentScreen == Screen::PATIENT_LOGIN) {
                handlePatientLogin(event);
            }
            else if (currentScreen == Screen::DOCTOR_LOGIN) {
                handleDoctorLogin(event);
            }
            else if (currentScreen == Screen::ADMIN_LOGIN) {
                handleAdminLogin(event);
            }
            else if (currentScreen == Screen::PATIENT_MENU) {
                handlePatientMenu(event);
            }
            else if (currentScreen == Screen::DOCTOR_MENU) {
                handleDoctorMenu(event);
            }
            else if (currentScreen == Screen::ADMIN_MENU) {
                handleAdminMenu(event);
            }
            else if (currentScreen == Screen::BOOK_APPOINTMENT) {
                handleBookAppointment(event);
            }
            else if (currentScreen == Screen::CANCEL_APPOINTMENT) {
                handleCancelAppointment(event);
            }
            else if (currentScreen == Screen::VIEW_APPOINTMENTS) {
                handleViewAppointments(event);
            }
            else if (currentScreen == Screen::VIEW_MEDICAL_RECORDS) {
                handleViewMedicalRecords(event);
            }
            else if (currentScreen == Screen::VIEW_BILLS) {
                handleViewBills(event);
            }
            else if (currentScreen == Screen::PAY_BILL) {
                handlePayBill(event);
            }
            else if (currentScreen == Screen::TOPUP_BALANCE) {
                handleTopUp(event);
            }
            else if (currentScreen == Screen::REGISTER_PATIENT) {
                handleRegisterPatient(event);
            }
            else if (currentScreen == Screen::VIEW_TODAY_APPTS) {
                handleViewTodayAppts(event);
            }
            else if (currentScreen == Screen::MARK_COMPLETE) {
                handleMarkComplete(event);
            }
            else if (currentScreen == Screen::MARK_NOSHOW) {
                handleMarkNoShow(event);
            }
            else if (currentScreen == Screen::WRITE_PRESCRIPTION) {
                handleWritePrescription(event);
            }
            else if (currentScreen == Screen::VIEW_PATIENT_HISTORY) {
                handleViewPatientHistory(event);
            }
            else if (currentScreen == Screen::ADD_DOCTOR) {
                handleAddDoctor(event);
            }
            else if (currentScreen == Screen::REMOVE_DOCTOR) {
                handleRemoveDoctor(event);
            }
            else if (currentScreen == Screen::VIEW_ALL_PATIENTS) {
                handleViewAllPatients(event);
            }
            else if (currentScreen == Screen::VIEW_ALL_DOCTORS) {
                handleViewAllDoctors(event);
            }
            else if (currentScreen == Screen::VIEW_ALL_APPOINTMENTS) {
                handleViewAllAppointments(event);
            }
            else if (currentScreen == Screen::VIEW_UNPAID_BILLS) {
                handleViewUnpaidBills(event);
            }
            else if (currentScreen == Screen::DISCHARGE_PATIENT) {
                handleDischargePatient(event);
            }
            else if (currentScreen == Screen::VIEW_SECURITY_LOG) {
                handleViewSecurityLog(event);
            }
            else if (currentScreen == Screen::DAILY_REPORT) {
                handleDailyReport(event);
            }
            else if (currentScreen == Screen::ADD_PATIENT) { 
                handleAddPatient(event); 
            }

            else if (currentScreen == Screen::REMOVE_PATIENT) { 
                handleRemovePatient(event);
            }
        }

        window.clear(sf::Color(10, 15, 40));

        if (currentScreen == Screen::MAIN_MENU) {
            drawMainMenu();
        }
        if (currentScreen == Screen::PATIENT_LOGIN) {
            drawLoginScreen("Patient Login");
        }
        if (currentScreen == Screen::DOCTOR_LOGIN) {
            drawLoginScreen("Doctor Login");
        }
        if (currentScreen == Screen::ADMIN_LOGIN) {
            drawLoginScreen("Admin Login");
        }
        if (currentScreen == Screen::PATIENT_MENU) {
            drawPatientMenu();
        }
        if (currentScreen == Screen::DOCTOR_MENU) {
            drawDoctorMenu();
        }
        if (currentScreen == Screen::ADMIN_MENU) {
            drawAdminMenu();
        }
        if (currentScreen == Screen::REGISTER_PATIENT) {
            drawRegisterPatient();
        }
        if (currentScreen == Screen::VIEW_APPOINTMENTS) {
            drawOutputScreen("My Appointments");
        }
        if (currentScreen == Screen::VIEW_MEDICAL_RECORDS) {
            drawOutputScreen("My Medical Records");
        }
        if (currentScreen == Screen::VIEW_BILLS) {
            drawOutputScreen("My Bills");
        }
        if (currentScreen == Screen::VIEW_TODAY_APPTS) {
            drawOutputScreen("Today's Appointments");
        }
        if (currentScreen == Screen::VIEW_ALL_PATIENTS) {
            drawOutputScreen("All Patients");
        }
        if (currentScreen == Screen::VIEW_ALL_DOCTORS) {
            drawOutputScreen("All Doctors");
        }
        if (currentScreen == Screen::VIEW_ALL_APPOINTMENTS) {
            drawOutputScreen("All Appointments");
        }
        if (currentScreen == Screen::VIEW_UNPAID_BILLS) {
            drawOutputScreen("Unpaid Bills");
        }
        if (currentScreen == Screen::VIEW_SECURITY_LOG) {
            drawOutputScreen("Security Log");
        }
        if (currentScreen == Screen::DAILY_REPORT) {
            drawOutputScreen("Daily Report");
        }
        if (currentScreen == Screen::VIEW_PATIENT_HISTORY) {
            if (inputStep == 0)
                drawInputScreen("Patient Medical History", "Patient ID");
            else
                drawOutputScreen("Patient Medical History");
        }
        if (currentScreen == Screen::BOOK_APPOINTMENT) {
            drawInputScreen("Book Appointment", "Input");
        }
        if (currentScreen == Screen::CANCEL_APPOINTMENT) {
            drawInputScreen("Cancel Appointment", "Appointment ID");
        }
        if (currentScreen == Screen::PAY_BILL) {
            drawInputScreen("Pay Bill", "Bill ID");
        }
        if (currentScreen == Screen::TOPUP_BALANCE) {
            drawInputScreen("Top Up Balance", "Amount (PKR)");
        }
        if (currentScreen == Screen::MARK_COMPLETE) {
            drawInputScreen("Mark Complete", "Appointment ID");
        }
        if (currentScreen == Screen::MARK_NOSHOW) {
            drawInputScreen("Mark No-Show", "Appointment ID");
        }
        if (currentScreen == Screen::WRITE_PRESCRIPTION) {
            drawInputScreen("Write Prescription", "Input");
        }
        if (currentScreen == Screen::ADD_DOCTOR) {
            drawInputScreen("Add Doctor", "Input");
        }
        if (currentScreen == Screen::REMOVE_DOCTOR) {
            drawInputScreen("Remove Doctor", "Doctor ID");
        }
        if (currentScreen == Screen::DISCHARGE_PATIENT) {
            drawInputScreen("Discharge Patient", "Patient ID");
        }
        if (currentScreen == Screen::ADD_PATIENT) {
            drawInputScreen("Add Patient", "Input"); 
        }
        if (currentScreen == Screen::REMOVE_PATIENT) {
            drawInputScreen("Remove Patient", "Patient ID"); 
        }

        window.display();
    }
}


void SFMLApp::handleMainMenu(sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up) {
            menuSelection = (menuSelection + 3) % 4;
        }
        if (event.key.code == sf::Keyboard::Down) {
            menuSelection = (menuSelection + 1) % 4;
        }
        if (event.key.code == sf::Keyboard::Return) {
            statusMessage[0] = '\0';
            inputString[0] = '\0';
            inputStep = 0;
            isPasswordField = false;
            if (menuSelection == 0) {
                currentScreen = Screen::PATIENT_LOGIN;
            }
            else if (menuSelection == 1) {
                currentScreen = Screen::DOCTOR_LOGIN;
            }
            else if (menuSelection == 2) {
                currentScreen = Screen::ADMIN_LOGIN;
            }
            else if (menuSelection == 3) {
                window.close();
            }
        }
    }

}

//same step karnai follow --> paihlai if esc, tou return else based on selection call the handle ya change the screen
void SFMLApp::handlePatientMenu(sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up) {
            menuSelection = (menuSelection + 7) % 8;
        }
        if (event.key.code == sf::Keyboard::Down) {
            menuSelection = (menuSelection + 1) % 8;
        }
        if (event.key.code == sf::Keyboard::Return) {
            statusMessage[0] = '\0';
            inputString[0] = '\0';
            inputStep = 0;
            displayBuffer[0] = '\0';
            isPasswordField = false;
            if (menuSelection == 0) {
                currentScreen = Screen::BOOK_APPOINTMENT;
            }
            else if (menuSelection == 1) {
                currentScreen = Screen::CANCEL_APPOINTMENT;
            }
            else if (menuSelection == 2) {
                currentScreen = Screen::VIEW_APPOINTMENTS;
                handleViewAppointments(event);
            }
            else if (menuSelection == 3) {
                currentScreen = Screen::VIEW_MEDICAL_RECORDS;
                handleViewMedicalRecords(event);
            }
            else if (menuSelection == 4) {
                currentScreen = Screen::VIEW_BILLS;
                handleViewBills(event);
            }
            else if (menuSelection == 5) {
                currentScreen = Screen::PAY_BILL;
            }
            else if (menuSelection == 6) {
                currentScreen = Screen::TOPUP_BALANCE;
            }
            else if (menuSelection == 7) {
                loggedPatient = nullptr;
                currentScreen = Screen::MAIN_MENU;
                menuSelection = 0;
            }
        }
    }
}


void SFMLApp::handleDoctorMenu(sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up) {
            menuSelection = (menuSelection + 5) % 6;
        }
        if (event.key.code == sf::Keyboard::Down) {
            menuSelection = (menuSelection + 1) % 6;
        }
        if (event.key.code == sf::Keyboard::Return) {
            statusMessage[0] = '\0';
            inputString[0] = '\0';
            inputStep = 0;
            displayBuffer[0] = '\0';
            isPasswordField = false;
            if (menuSelection == 0) {
                currentScreen = Screen::VIEW_TODAY_APPTS;
                handleViewTodayAppts(event);
            }
            else if (menuSelection == 1) {
                currentScreen = Screen::MARK_COMPLETE;
            }
            else if (menuSelection == 2) {
                currentScreen = Screen::MARK_NOSHOW;
            }
            else if (menuSelection == 3) {
                currentScreen = Screen::WRITE_PRESCRIPTION;
            }
            else if (menuSelection == 4) {
                currentScreen = Screen::VIEW_PATIENT_HISTORY;
            }
            else if (menuSelection == 5) {
                loggedDoctor = nullptr; currentScreen = Screen::MAIN_MENU; menuSelection = 0;
            }
        }
    }
}

void SFMLApp::handleAdminMenu(sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up) {
            menuSelection = (menuSelection + 11) % 12;
        }
        if (event.key.code == sf::Keyboard::Down) {
            menuSelection = (menuSelection + 1) % 12;
        }
        if (event.key.code == sf::Keyboard::Return) {
            statusMessage[0] = '\0';
            inputString[0] = '\0';
            inputStep = 0;
            displayBuffer[0] = '\0';
            isPasswordField = false;
            if (menuSelection == 0) {
                currentScreen = Screen::ADD_DOCTOR;
            }
            else if (menuSelection == 1) {
                currentScreen = Screen::REMOVE_DOCTOR;
            }
            else if (menuSelection == 2) { 
                currentScreen = Screen::ADD_PATIENT;
            }        
            else if (menuSelection == 3) {
                currentScreen = Screen::REMOVE_PATIENT;
            }
            else if (menuSelection == 4) {
                currentScreen = Screen::VIEW_ALL_PATIENTS;
                handleViewAllPatients(event);
            }
            else if (menuSelection == 5) {
                currentScreen = Screen::VIEW_ALL_DOCTORS;
                handleViewAllDoctors(event);
            }
            else if (menuSelection == 6) {
                currentScreen = Screen::VIEW_ALL_APPOINTMENTS;
                handleViewAllAppointments(event);
            }
            else if (menuSelection == 7) {
                currentScreen = Screen::VIEW_UNPAID_BILLS;
                handleViewUnpaidBills(event);
            }
            else if (menuSelection == 8) {
                currentScreen = Screen::DISCHARGE_PATIENT;
            }
            else if (menuSelection == 9) {
                currentScreen = Screen::VIEW_SECURITY_LOG;
                handleViewSecurityLog(event);
            }
            else if (menuSelection == 10) {
                currentScreen = Screen::DAILY_REPORT;
                handleDailyReport(event);
            }
            else if (menuSelection == 11) {
                loggedAdmin = nullptr; currentScreen = Screen::MAIN_MENU; menuSelection = 0;
            }
        }
    }
}

//steps same for all three login:
/*
did user enter to go back
are we on the input step 0 --> userID
are we on the input step 2 --> password
compare credentials
give the session variable i.e loggedPatient the patient pointer we made if credentials match
move to the next screen

*/
void SFMLApp::handlePatientLogin(sf::Event& event) {
    static char idStore[20] = "";
    static char passwordStore[100] = "";

    //1. Exits -->esc
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        currentScreen = Screen::MAIN_MENU;
        idStore[0] = '\0';
        passwordStore[0] = '\0';
        inputStep = 0;
        statusMessage[0] = '\0';
        return;
    }
    //if R presed --> register patient menu 
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R && inputStep == 0) {
        currentScreen = Screen::REGISTER_PATIENT;
        inputStep = 0;
        inputString[0] = '\0';
        displayBuffer[0] = '\0';
        statusMessage[0] = '\0';
        return;
    }

    //if ID rnn --> then while length lesser than 19 store
    if (inputStep == 0) {
        isPasswordField = false;
        if (event.type == sf::Event::TextEntered) {
            if (event.text.unicode == 8 && customStrLen(idStore) > 0) {
                idStore[customStrLen(idStore) - 1] = '\0';
            }
            else if (event.text.unicode >= '0' && event.text.unicode <= '9') {
                int len = customStrLen(idStore);
                if (len < 19) {
                    idStore[len] = (char)event.text.unicode;
                    idStore[len + 1] = '\0';
                }
            }
        }
        StrCpyFunction(inputString, idStore);


        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return && customStrLen(idStore) > 0) {
            inputStep = 1;
            passwordStore[0] = '\0';
            inputString[0] = '\0';
            StrCpyFunction(enteredIDDisplay, idStore);
        }
    }
    else {
        isPasswordField = true;
        if (event.type == sf::Event::TextEntered) {
            if (event.text.unicode == 8 && customStrLen(passwordStore) > 0) {
                passwordStore[customStrLen(passwordStore) - 1] = '\0';
            }
            else if (event.text.unicode >= 32 && event.text.unicode < 127) {
                int len = customStrLen(passwordStore);
                if (len < 99) {
                    passwordStore[len] = (char)event.text.unicode;
                    passwordStore[len + 1] = '\0';
                }
            }
        }
        StrCpyFunction(inputString, passwordStore);
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return) {
            int id = 0;
            for (int i = 0; idStore[i] != '\0'; i++) {
                id = id * 10 + (idStore[i] - '0');
            }
            Patient* patient = findPatientByCredentials(id, passwordStore); //Patient object pointer
            if (patient) {
                loggedPatient = patient;
                loginFailCount = 0;
                currentScreen = Screen::PATIENT_MENU;
                menuSelection = 0;
                idStore[0] = '\0';
                passwordStore[0] = '\0';
                inputStep = 0;
                statusMessage[0] = '\0';
                isPasswordField = false;
                enteredIDDisplay[0] = '\0';

                
            }
            else {
                //if patient not logged in then security log needs to have it
                loginFailCount++;
                FileHandler::logSecurityEvent("Patient", id, "FAILED");
                if (loginFailCount >= 3) {
                    StrCpyFunction(statusMessage, "Account locked. Contact admin.");
                    idStore[0] = '\0';
                    passwordStore[0] = '\0';
                    inputStep = 0;
                }
                else {
                    char msg[200];
                    StrCpyFunction(msg, "Invalid credentials. Attempt ");
                    char attemptNum[10];
                    intToStrFunction(loginFailCount, attemptNum, 10);
                    strcatFunction(msg, attemptNum);
                    strcatFunction(msg, "/3");
                    StrCpyFunction(statusMessage, msg);
                    passwordStore[0] = '\0';
                    inputString[0] = '\0';
                }
            }
        }
    }
}
//doctor login and admin login same steps hain

void SFMLApp::handleDoctorLogin(sf::Event& event) {
    static char idBuffer[20] = "";
    static char passwordBuffer[100] = "";

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        currentScreen = Screen::MAIN_MENU;
        idBuffer[0] = '\0';
        passwordBuffer[0] = '\0';
        inputStep = 0;
        statusMessage[0] = '\0';
        return;
    }

    if (inputStep == 0) {
        isPasswordField = false;
        if (event.type == sf::Event::TextEntered) {
            if (event.text.unicode == 8 && customStrLen(idBuffer) > 0) {
                idBuffer[customStrLen(idBuffer) - 1] = '\0';
            }
            else if (event.text.unicode >= '0' && event.text.unicode <= '9') {
                int len = customStrLen(idBuffer);
                if (len < 19) {
                    idBuffer[len] = (char)event.text.unicode;
                    idBuffer[len + 1] = '\0';
                }
            }
        }
        StrCpyFunction(inputString, idBuffer);
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return && customStrLen(idBuffer) > 0) {
            inputStep = 1;
            passwordBuffer[0] = '\0';
            inputString[0] = '\0';
            StrCpyFunction(enteredIDDisplay, idBuffer);
        }
    }
    else {
        isPasswordField = true;
        if (event.type == sf::Event::TextEntered) {
            if (event.text.unicode == 8 && customStrLen(passwordBuffer) > 0) {
                passwordBuffer[customStrLen(passwordBuffer) - 1] = '\0';
            }
            else if (event.text.unicode >= 32 && event.text.unicode < 127) {
                int len = customStrLen(passwordBuffer);
                if (len < 99) {
                    passwordBuffer[len] = (char)event.text.unicode;
                    passwordBuffer[len + 1] = '\0';
                }
            }
        }
        StrCpyFunction(inputString, passwordBuffer);
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return) {
            int id = 0;
            for (int i = 0; idBuffer[i] != '\0'; i++) {
                id = id * 10 + (idBuffer[i] - '0');
            }
            Doctor* doctor = findDoctorByCredentials(id, passwordBuffer);
            if (doctor) {
                loggedDoctor = doctor;
                loginFailCount = 0;
                currentScreen = Screen::DOCTOR_MENU;
                menuSelection = 0;
                idBuffer[0] = '\0';
                passwordBuffer[0] = '\0';
                inputStep = 0;
                statusMessage[0] = '\0';
                isPasswordField = false;
                enteredIDDisplay[0] = '\0';
            }
            else {
                loginFailCount++;
                FileHandler::logSecurityEvent("Doctor", id, "FAILED");
                if (loginFailCount >= 3) {
                    StrCpyFunction(statusMessage, "Account locked. Contact admin.");
                    idBuffer[0] = '\0';
                    passwordBuffer[0] = '\0';
                    inputStep = 0;
                }
                else {
                    char msg[200];
                    StrCpyFunction(msg, "Invalid credentials. Attempt ");
                    char attemptNum[10];
                    intToStrFunction(loginFailCount, attemptNum, 10);
                    strcatFunction(msg, attemptNum);
                    strcatFunction(msg, "/3");
                    StrCpyFunction(statusMessage, msg);
                    passwordBuffer[0] = '\0';
                    inputString[0] = '\0';
                }
            }
        }
    }
}

void SFMLApp::handleAdminLogin(sf::Event& event) {
    static char idBuffer[20] = "";
    static char passwordBuffer[100] = "";

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        currentScreen = Screen::MAIN_MENU;
        idBuffer[0] = '\0';
        passwordBuffer[0] = '\0';
        inputStep = 0;
        statusMessage[0] = '\0';
        return;
    }

    if (inputStep == 0) {
        isPasswordField = false;
        if (event.type == sf::Event::TextEntered) {
            if (event.text.unicode == 8 && customStrLen(idBuffer) > 0) {
                idBuffer[customStrLen(idBuffer) - 1] = '\0';
            }
            else if (event.text.unicode >= '0' && event.text.unicode <= '9') {
                int len = customStrLen(idBuffer);
                if (len < 19) {
                    idBuffer[len] = (char)event.text.unicode;
                    idBuffer[len + 1] = '\0';
                }
            }
        }
        StrCpyFunction(inputString, idBuffer);
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return && customStrLen(idBuffer) > 0) {
            inputStep = 1;
            passwordBuffer[0] = '\0';
            inputString[0] = '\0';
            StrCpyFunction(enteredIDDisplay, idBuffer);
        }
    }
    else {
        isPasswordField = true;
        if (event.type == sf::Event::TextEntered) {
            if (event.text.unicode == 8 && customStrLen(passwordBuffer) > 0) {
                passwordBuffer[customStrLen(passwordBuffer) - 1] = '\0';
            }
            else if (event.text.unicode >= 32 && event.text.unicode < 127) {
                int len = customStrLen(passwordBuffer);
                if (len < 99) {
                    passwordBuffer[len] = (char)event.text.unicode;
                    passwordBuffer[len + 1] = '\0';
                }
            }
        }
        StrCpyFunction(inputString, passwordBuffer);
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return) {
            int id = 0;
            for (int i = 0; idBuffer[i] != '\0'; i++) {
                id = id * 10 + (idBuffer[i] - '0');
            }
            Admin* admin = findAdminByCredentials(id, passwordBuffer);
            if (admin) {
                loggedAdmin = admin;
                loginFailCount = 0;
                currentScreen = Screen::ADMIN_MENU;
                menuSelection = 0;
                idBuffer[0] = '\0';
                passwordBuffer[0] = '\0';
                inputStep = 0;
                statusMessage[0] = '\0';
                isPasswordField = false;
                enteredIDDisplay[0] = '\0';
            }
            else {
                loginFailCount++;
                FileHandler::logSecurityEvent("Admin", id, "FAILED");
                if (loginFailCount >= 3) {
                    StrCpyFunction(statusMessage, "Account locked. Contact admin.");
                    idBuffer[0] = '\0';
                    passwordBuffer[0] = '\0';
                    inputStep = 0;
                }
                else {
                    char msg[200];
                    StrCpyFunction(msg, "Invalid credentials. Attempt ");
                    char attemptNum[10];
                    intToStrFunction(loginFailCount, attemptNum, 10);
                    strcatFunction(msg, attemptNum);
                    strcatFunction(msg, "/3");
                    StrCpyFunction(statusMessage, msg);
                    passwordBuffer[0] = '\0';
                    inputString[0] = '\0';
                }
            }
        }
    }
}

//Register in 6 steps -->each alag output screen
/*
like again agar R --> wapis patient login now
point to current field
input step ka kaam to keep track of which step we on
each step par required validation daalni and phir
creating a new object patient --> appending to file -->reload and success message

*/
void SFMLApp::handleRegisterPatient(sf::Event& event) {
    static char nameStore[100] = "";
    static char ageStore[10] = "";
    static char genderStore[5] = "";
    static char contactStore[20] = "";
    static char passwordStore[100] = "";
    static char balanceStore[50] = "";

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        currentScreen = Screen::PATIENT_LOGIN;
        inputStep = 0;
        inputString[0] = '\0';
        nameStore[0] = ageStore[0] = genderStore[0] = contactStore[0] = passwordStore[0] = balanceStore[0] = '\0';
        statusMessage[0] = '\0';
        isPasswordField = false;
        return;
    }

    char* currentField = nullptr;
    if (inputStep == 0) {
        currentField = nameStore;
        isPasswordField = false;
    }
    else if (inputStep == 1) {
        currentField = ageStore;
    }
    else if (inputStep == 2) {
        currentField = genderStore;
    }
    else if (inputStep == 3) {
        currentField = contactStore;
    }
    else if (inputStep == 4) {
        currentField = passwordStore;
        isPasswordField = true;
    }
    else if (inputStep == 5) {
        currentField = balanceStore;
        isPasswordField = false;
    }

    if (currentField && event.type == sf::Event::TextEntered) {
        if (event.text.unicode == 8 && customStrLen(currentField) > 0) {
            currentField[customStrLen(currentField) - 1] = '\0';
        }
        else if (event.text.unicode >= 32 && event.text.unicode < 127) {
            int len = customStrLen(currentField);
            if (len < 99) {
                currentField[len] = (char)event.text.unicode;
                currentField[len + 1] = '\0';
            }
        }
        StrCpyFunction(inputString, currentField);
    }

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return) {
        statusMessage[0] = '\0';
        if (inputStep == 0) {
            if (customStrLen(nameStore) == 0 || customStrLen(nameStore) > 50) {
                StrCpyFunction(statusMessage, "Name must be 1-50 chars.");
                return;
            }
            inputStep = 1;
            StrCpyFunction(inputString, ageStore);
        }
        else if (inputStep == 1) {
            bool valid = (customStrLen(ageStore) > 0);
            for (int i = 0; ageStore[i] != '\0'; i++) {
                if (ageStore[i] < '0' || ageStore[i] > '9') { valid = false; break; }
            }
            if (!valid) { StrCpyFunction(statusMessage, "Enter a valid age."); return; }
            inputStep = 2;
            StrCpyFunction(inputString, genderStore);
        }
        else if (inputStep == 2) {
            if ((genderStore[0] != 'M' && genderStore[0] != 'F' && genderStore[0] != 'm' && genderStore[0] != 'f') || customStrLen(genderStore) != 1) {
                StrCpyFunction(statusMessage, "Gender must be M or F.");
                return;
            }
            inputStep = 3;
            StrCpyFunction(inputString, contactStore);
        }
        else if (inputStep == 3) {
            char contactArray[12];
            copyToStore(contactArray, contactStore, 12);
            if (!Validator::isValidContact(contactArray)) {
                StrCpyFunction(statusMessage, "Contact must be exactly 11 digits.");
                return;
            }
            inputStep = 4;
            inputString[0] = '\0';
        }
        else if (inputStep == 4) {
            char passArray[51];
            copyToStore(passArray, passwordStore, 51);
            if (!Validator::isValidPassword(passArray)) {
                StrCpyFunction(statusMessage, "Password must be at least 6 chars.");
                return;
            }
            inputStep = 5;
            StrCpyFunction(inputString, balanceStore);
            isPasswordField = false;
        }
        else if (inputStep == 5) {
            bool valid = (customStrLen(balanceStore) > 0);
            for (int i = 0; balanceStore[i] != '\0'; i++) {
                if (balanceStore[i] != '.' && (balanceStore[i] < '0' || balanceStore[i] > '9')) { valid = false; break; }
            }
            if (!valid) { StrCpyFunction(statusMessage, "Enter a valid balance."); return; }

            double balance = 0.0;
            bool   hasDot = false;
            double decimal = 0.1;
            for (int i = 0; balanceStore[i] != '\0'; i++) {
                if (balanceStore[i] == '.') { hasDot = true; }
                else if (!hasDot) { balance = balance * 10 + (balanceStore[i] - '0'); }
                else { balance += decimal * (balanceStore[i] - '0'); decimal *= 0.1; }
            }

            int newID = FileHandler::getFilePatientID();
            char gender = (genderStore[0] == 'm') ? 'M' : (genderStore[0] == 'f') ? 'F' : genderStore[0];
            int age = 0;
            for (int i = 0; ageStore[i] != '\0'; i++) { age = age * 10 + (ageStore[i] - '0'); }

            Patient newPatient(newID, nameStore, passwordStore, false, balance, gender, age, contactStore, 0);
            FileHandler::appendPatient(newPatient);
            reloadAllData();
            //so that when user enters again we can ensure it does allow user to enter
            char msg[200];
            StrCpyFunction(msg, "Registered! Your ID is ");
            char idStr[20];
            intToStrFunction(newID, idStr, 20);
            strcatFunction(msg, idStr);
            strcatFunction(msg, ". Press ESC to login.");
            StrCpyFunction(statusMessage, msg);
            nameStore[0] = ageStore[0] = genderStore[0] = contactStore[0] = passwordStore[0] = balanceStore[0] = '\0';
            inputStep = 0;
            inputString[0] = '\0';
        }
    }

    char stepInfo[500];
    StrCpyFunction(stepInfo, "Step ");
    char stepNum[10];
    intToStrFunction(inputStep + 1, stepNum, 10);
    strcatFunction(stepInfo, stepNum);
    strcatFunction(stepInfo, " of 6\n");
    StrCpyFunction(displayBuffer, stepInfo);
    if (customStrLen(nameStore) > 0) {
        char line[200];
        StrCpyFunction(line, "Name: ");
        strcatFunction(line, nameStore);
        strcatFunction(line, "\n");
        strcatFunction(displayBuffer, line);
    }
    if (customStrLen(ageStore) > 0) {
        char line[200];
        StrCpyFunction(line, "Age: ");
        strcatFunction(line, ageStore);
        strcatFunction(line, "\n");
        strcatFunction(displayBuffer, line);
    }
    if (customStrLen(genderStore) > 0) {
        char line[200];
        StrCpyFunction(line, "Gender: ");
        strcatFunction(line, genderStore);
        strcatFunction(line, "\n");
        strcatFunction(displayBuffer, line);
    }
    if (customStrLen(contactStore) > 0) {
        char line[200];
        StrCpyFunction(line, "Contact: ");
        strcatFunction(line, contactStore);
        strcatFunction(line, "\n");
        strcatFunction(displayBuffer, line);
    }
}

//How to handle --> basically appointment array banao --> add all appointments of patient into that 
//sort it and then bus compare and constaantly output every appointment in a new line
void SFMLApp::handleViewAppointments(sf::Event& event) {
    //basically aik cheez current screen always basically becomes the next screen to display after event
    if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::B)) {
        currentScreen = Screen::PATIENT_MENU;
        displayBuffer[0] = '\0';
        return;
    }
    //so that only runs once
    if (customStrLen(displayBuffer) == 0) {
        Appointment array[100];
        int count = 0;
        for (int i = 0; i < appointments.arraySize(); i++) {
            Appointment& appointmentObject = appointments.getAll()[i];
            if (appointmentObject.getPatientID() == loggedPatient->getPatientID()) {
                array[count++] = appointmentObject;
            }
        }
        sortAppointmentsByDate(array, count, true);
        if (count == 0) {
            StrCpyFunction(displayBuffer, "No appointments found.");
            return;
        }
        StrCpyFunction(displayBuffer, "ID | Doctor ID | Date | Slot | Status\n");
        for (int i = 0; i < count; i++) {
            char row[200];
            char IDstring[20];
            char doctorIDString[20];
            intToStrFunction(array[i].getAppointmentID(), IDstring, 20);
            intToStrFunction(array[i].getDoctorID(), doctorIDString, 20);
            StrCpyFunction(row, IDstring);
            strcatFunction(row, " | ");
            strcatFunction(row, doctorIDString);
            strcatFunction(row, " | ");
            strcatFunction(row, array[i].getDate());
            strcatFunction(row, " | ");
            strcatFunction(row, array[i].getTimeSlot());
            strcatFunction(row, " | ");
            strcatFunction(row, array[i].getStatus());
            strcatFunction(row, "\n");
            strcatFunction(displayBuffer, row);
        }
    }
}
// again if user presses esc -->return to prev menu
//else same steps as appointment
void SFMLApp::handleViewMedicalRecords(sf::Event& event) {
    if (event.type == sf::Event::KeyPressed &&
        (event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::B)) {
        currentScreen = Screen::PATIENT_MENU;
        displayBuffer[0] = '\0';
        return;
    }
    if (customStrLen(displayBuffer) == 0) {
        Prescription arr[100];
        int count = 0;
        for (int i = 0; i < prescriptions.arraySize(); i++) {
            Prescription& pr = prescriptions.getAll()[i];
            if (pr.getpatientID() == loggedPatient->getPatientID()) {
                arr[count++] = pr;
            }
        }
        sortPrescriptionsByDate(arr, count, true);
        if (count == 0) {
            StrCpyFunction(displayBuffer, "No medical records found.");
            return;
        }
        StrCpyFunction(displayBuffer, "Date | Doctor ID | Medicines | Notes \n");
        for (int i = 0; i < count; i++) {
            char row[500];
            char docIdStr[20];
            intToStrFunction(arr[i].getdoctorID(), docIdStr, 20);
            StrCpyFunction(row, arr[i].getDate());
            strcatFunction(row, " | ");
            strcatFunction(row, docIdStr);
            strcatFunction(row, " | ");
            strcatFunction(row, arr[i].getMedicine());
            strcatFunction(row, " | ");
            strcatFunction(row, arr[i].getNotes());
            strcatFunction(row, "\n\n");
            strcatFunction(displayBuffer, row);
        }
    }
}

//same steps for bill except bill will have both ids 
void SFMLApp::handleViewBills(sf::Event& event) {
    if (event.type == sf::Event::KeyPressed &&
        (event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::B)) {
        currentScreen = Screen::PATIENT_MENU;
        displayBuffer[0] = '\0';
        return;
    }
    double totalOutstanding = 0.0;
    bool   anyBills = false;
    if (customStrLen(displayBuffer) == 0) {
        StrCpyFunction(displayBuffer, "Bill ID | Appt ID | Amount | Status | Date\n");
        for (int i = 0; i < bills.arraySize(); i++) {
            Bill& bill = bills.getAll()[i]; // basically reference to bill storaage template where we have all stored from thhe fles
            if (bill.getPatientID() == loggedPatient->getPatientID()) {
                char row[200];
                char billIdStr[20];
                char appointmentIDStr[20];
                char amountStr[50];
                intToStrFunction(bill.getBillID(), billIdStr, 20);
                intToStrFunction(bill.getAppointmentID(), appointmentIDStr, 20);
                customDoubleToStr(bill.getAmount(), amountStr, 50);
                StrCpyFunction(row, billIdStr);
                strcatFunction(row, " | ");
                strcatFunction(row, appointmentIDStr);
                strcatFunction(row, " | PKR ");
                strcatFunction(row, amountStr);
                strcatFunction(row, " | ");
                strcatFunction(row, bill.getStatus());
                strcatFunction(row, " | ");
                strcatFunction(row, bill.getDate());
                strcatFunction(row, "\n");
                strcatFunction(displayBuffer, row);
                if (stringEqual(bill.getStatus(), "unpaid")) {
                    totalOutstanding += bill.getAmount();
                }
                anyBills = true;
            }
        }
        if (!anyBills) {
            StrCpyFunction(displayBuffer, "No bills found.");
            return;
        }
        char total[100];
        char totalAmount[50];
        customDoubleToStr(totalOutstanding, totalAmount, 50);
        StrCpyFunction(total, "\nTotal Outstanding: PKR ");
        strcatFunction(total, totalAmount);
        strcatFunction(displayBuffer, total);
    }
}
//Handles booking of appointment
void SFMLApp::handleBookAppointment(sf::Event& event) {
    static char specialityStore[100] = "";
    static char doctorIDStore[20] = "";
    static char dateStore[20] = "";
    static char slotStore[10] = "";
    static char availableSlots[20][6];
    static Doctor matchingDoctors[50];
    static int matchingCount = 0;

    //wahi if r pressed return to prev screen i.e patient menu
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        currentScreen = Screen::PATIENT_MENU;
        specialityStore[0] = doctorIDStore[0] = dateStore[0] = slotStore[0] = '\0';
        inputStep = 0;
        inputString[0] = '\0';
        statusMessage[0] = '\0';
        return;
    }

    //current field tells on which screen/ option we are on
    char* currentField = nullptr;
    if (inputStep == 0) {
        currentField = specialityStore;
    }
    else if (inputStep == 1) {
        currentField = doctorIDStore; 
    }
    else if (inputStep == 2) { 
        currentField = dateStore;
    }
    else if (inputStep == 3) { 
        currentField = slotStore;
    }

    //basically ensuring that all keypresses are handled whether backpsace 8 wali cheez and uss kai ilawa bhi
    if (currentField && event.type == sf::Event::TextEntered) {
        if (event.text.unicode == 8 && customStrLen(currentField) > 0) {
            currentField[customStrLen(currentField) - 1] = '\0';
        }
        else if (event.text.unicode >= 32 && event.text.unicode < 127) {
            int len = customStrLen(currentField);
            if (len < 99) {
                currentField[len] = (char)event.text.unicode;
                currentField[len + 1] = '\0';
            }
        }
        StrCpyFunction(inputString, currentField);
    }

    //agar entered press
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return) {
        statusMessage[0] = '\0';

        //agar first state, we make a doctor reference, check if specialization of doctor same 
        // agar hai phir matching doctor mai doctor
        if (inputStep == 0) {
            matchingCount = 0;
            for (int i = 0; i < doctors.arraySize(); i++) {
                Doctor& doctorReference = doctors.getAll()[i];
                if (stringEqualCase(doctorReference.getSpecialization(), specialityStore)) {
                    matchingDoctors[matchingCount++] = doctorReference;
                }
            }
            //agar count nhi hai statusmessage mai no doctor available daal detai
            if (matchingCount == 0) {
                StrCpyFunction(statusMessage, "No doctors available for that specialization.");
                specialityStore[0] = '\0';
                inputString[0] = '\0';
                return;
            }
           //jitnai doctors utni dafa loop and output
            StrCpyFunction(displayBuffer, "Doctors found:\n");
            for (int i = 0; i < matchingCount; i++) {
                char row[200];
                char docIdStr[20];
                char feeStr[50];
                intToStrFunction(matchingDoctors[i].getDoctorID(), docIdStr, 20);
                customDoubleToStr(matchingDoctors[i].getFee(), feeStr, 50);
                StrCpyFunction(row, "ID: ");
                strcatFunction(row, docIdStr);
                strcatFunction(row, " | ");
                strcatFunction(row, matchingDoctors[i].getName());
                strcatFunction(row, " | Fee: PKR ");
                strcatFunction(row, feeStr);
                strcatFunction(row, "\n");
                strcatFunction(displayBuffer, row);
            }
            //phir doctorID
            strcatFunction(displayBuffer, "\nEnter Doctor ID:");
            inputStep = 1;
            doctorIDStore[0] = '\0';
            inputString[0] = '\0';
        }
        //Agar next step --> doctor index chahiyai
        else if (inputStep == 1) {
            int doctorID = 0;
            for (int i = 0; doctorIDStore[i] != '\0'; i++) {
                doctorID = doctorID * 10 + (doctorIDStore[i] - '0');
            }
            bookDoctorIndex = -1;
            for (int i = 0; i < matchingCount; i++) {
                if (matchingDoctors[i].getDoctorID() == doctorID) {
                    bookDoctorIndex = i;
                    break;
                }
            }
            //agar doctor no found phir
            if (bookDoctorIndex == -1) {
                StrCpyFunction(statusMessage, "Doctor not found.");
                doctorIDStore[0] = '\0';
                inputString[0] = '\0';
                return;
            }
            //Phir ab date 
            StrCpyFunction(displayBuffer, "Enter date (DD-MM-YYYY):");
            inputStep = 2;
            dateStore[0] = '\0';
            inputString[0] = '\0';
        }
        else if (inputStep == 2) {
            char dateArray[11];
            copyToStore(dateArray, dateStore, 11);
            //date ko sahi format mai bhi rukhna na ham nai
            if (!Validator::isValidDate(dateArray)) {
                StrCpyFunction(statusMessage, "Invalid date. Use format DD-MM-YYYY.");
                dateStore[0] = '\0';
                inputString[0] = '\0';
                return;
            }
            char today[11];
            getTodayDate(today);
            //calculation to onvert the date into a integer time
            int enteredInt = ((dateArray[6] - '0') * 1000 + (dateArray[7] - '0') * 100 + (dateArray[8] - '0') * 10 + (dateArray[9] - '0')) * 10000
                + ((dateArray[3] - '0') * 10 + (dateArray[4] - '0')) * 100
                + (dateArray[0] - '0') * 10 + (dateArray[1] - '0');
            int todayInt = ((today[6] - '0') * 1000 + (today[7] - '0') * 100 + (today[8] - '0') * 10 + (today[9] - '0')) * 10000
                + ((today[3] - '0') * 10 + (today[4] - '0')) * 100
                + (today[0] - '0') * 10 + (today[1] - '0');
            if (enteredInt < todayInt) {
                StrCpyFunction(statusMessage, "Cannot book appointment for a past date.");
                dateStore[0] = '\0';
                inputString[0] = '\0';
                return;
            }
            int doctorID = matchingDoctors[bookDoctorIndex].getDoctorID();
            int slotCount = buildAvailableSlots(doctorID, dateArray, availableSlots);
            StrCpyFunction(displayBuffer, "Available slots:\n");
            for (int i = 0; i < slotCount; i++) {
                strcatFunction(displayBuffer, availableSlots[i]);
                strcatFunction(displayBuffer, "\n");
            }
            if (slotCount == 0) {
                StrCpyFunction(displayBuffer, "No slots available on this date.\n");
            }
            strcatFunction(displayBuffer, "\nEnter time slot (e.g. 09:00):");
            inputStep = 3;
            slotStore[0] = '\0';
            inputString[0] = '\0';
        }
        else if (inputStep == 3) {
            char slotArray[6];
            copyToStore(slotArray, slotStore, 6);
            //phir time slots aajatai
            if (!Validator::isValidTime(slotArray)) {
                StrCpyFunction(statusMessage, "Invalid time slot.");
                slotStore[0] = '\0';
                inputString[0] = '\0';
                return;
            }
            char dateArray[11];
            copyToStore(dateArray, dateStore, 11);
            int doctorID = matchingDoctors[bookDoctorIndex].getDoctorID();
            bool taken = false;
            for (int i = 0; i < appointments.arraySize(); i++) {
                Appointment& appointmentReference = appointments.getAll()[i];
                if (appointmentReference.getDoctorID() == doctorID &&
                    stringEqual(appointmentReference.getDate(), dateArray) &&
                    stringEqual(appointmentReference.getTimeSlot(), slotArray) &&
                    !stringEqual(appointmentReference.getStatus(), "cancelled")) {
                    taken = true;
                    break;
                }
            }
            if (taken) {
                StrCpyFunction(statusMessage, "This time slot is already booked. Please choose another.");
                slotStore[0] = '\0';
                inputString[0] = '\0';
                return;
            }
            double fee = matchingDoctors[bookDoctorIndex].getFee();
            if (loggedPatient->getBalance() < fee) {
                StrCpyFunction(statusMessage, "Insufficient funds. Please top up your balance.");
                currentScreen = Screen::PATIENT_MENU;
                displayBuffer[0] = '\0';
                return;
            }
            *loggedPatient -= fee;
            int appointmentID = FileHandler::getFileAppointmentID();

            Appointment newAppointment(appointmentID, loggedPatient->getPatientID(), doctorID, dateArray, slotArray, "pending", true);
            FileHandler::appendAppointment(newAppointment);
            FileHandler::updatePatient(*loggedPatient);
            int billID = FileHandler::geFileBillID();
            Bill newBill(billID, loggedPatient->getPatientID(), appointmentID, fee, "paid", dateArray);
            FileHandler::appendBill(newBill);
            reloadAllData();
            loggedPatient = patients.findID(loggedPatient->getPatientID());
            char msg[200];
            StrCpyFunction(msg, "Appointment booked! ID: ");
            char idStr[20];
            intToStrFunction(appointmentID, idStr, 20);
            strcatFunction(msg, idStr);
            StrCpyFunction(statusMessage, msg);
            currentScreen = Screen::PATIENT_MENU;
            specialityStore[0] = doctorIDStore[0] = dateStore[0] = slotStore[0] = '\0';
            inputStep = 0;
            inputString[0] = '\0';
        }
    }

    if (inputStep == 0 && customStrLen(displayBuffer) == 0) {
        StrCpyFunction(displayBuffer, "Enter specialization (e.g. Cardiology):");
    }
}

void SFMLApp::handleCancelAppointment(sf::Event& event) {
    static char appointmentIDStore[20] = "";

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        currentScreen = Screen::PATIENT_MENU;
        appointmentIDStore[0] = '\0';
        inputStep = 0;
        inputString[0] = '\0';
        statusMessage[0] = '\0';
        displayBuffer[0] = '\0';
        return;
    }
    if (event.type == sf::Event::TextEntered) {
        if (event.text.unicode == 8 && customStrLen(appointmentIDStore) > 0) {
            appointmentIDStore[customStrLen(appointmentIDStore) - 1] = '\0';
        }
        else if (event.text.unicode >= '0' && event.text.unicode <= '9') {
            int len = customStrLen(appointmentIDStore);
            if (len < 19) {
                appointmentIDStore[len] = (char)event.text.unicode;
                appointmentIDStore[len + 1] = '\0';
            }
        }
        StrCpyFunction(inputString, appointmentIDStore);
    }


    if (customStrLen(displayBuffer) == 0) {
        StrCpyFunction(displayBuffer, "Pending appointments:\n");
        bool anyPending = false;
        //check whether anything pending
        //checks if pending displays
        for (int i = 0; i < appointments.arraySize(); i++) {
            Appointment& appointmentReference = appointments.getAll()[i];
            if (appointmentReference.getPatientID() == loggedPatient->getPatientID() && stringEqual(appointmentReference.getStatus(), "pending")) {
                char row[200];
                char appointmentIDString[20];
                char doctorIDString[20];
                intToStrFunction(appointmentReference.getAppointmentID(), appointmentIDString, 20);
                intToStrFunction(appointmentReference.getDoctorID(), doctorIDString, 20);
                StrCpyFunction(row, "ID: ");
                strcatFunction(row, appointmentIDString);
                strcatFunction(row, " | Doctor: ");
                strcatFunction(row, doctorIDString);
                strcatFunction(row, " | ");
                strcatFunction(row, appointmentReference.getDate());
                strcatFunction(row, " | ");
                strcatFunction(row, appointmentReference.getTimeSlot());
                strcatFunction(row, "\n\n");
                strcatFunction(displayBuffer, row);
                anyPending = true;
            }
        }
        if (!anyPending) {
            StrCpyFunction(displayBuffer, "You have no pending appointments.");
        }
        strcatFunction(displayBuffer, "\nEnter Appointment ID to cancel:");
    }

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return && customStrLen(appointmentIDStore) > 0) {
        int appointmentID = 0;
        for (int i = 0; appointmentIDStore[i] != '\0'; i++) {
            appointmentID = appointmentID * 10 + (appointmentIDStore[i] - '0');
        }
        //Agar appointmentID wrong , ya patientID wrong ya not pending
        Appointment* appointmentObject = appointments.findID(appointmentID);
        if (!appointmentObject || appointmentObject->getPatientID() != loggedPatient->getPatientID() || !stringEqual(appointmentObject->getStatus(), "pending")) {
            StrCpyFunction(statusMessage, "Invalid appointment ID.");
            appointmentIDStore[0] = '\0';
            inputString[0] = '\0';
            return;
        }
        Doctor* doctorObject = doctors.findID(appointmentObject->getDoctorID());
        double fee;

        if (doctorObject) {
            fee = doctorObject->getFee();
        }
        else {
            fee = 0.0;
        }        appointmentObject->setStatus("cancelled");

        FileHandler::updateAppointment(*appointmentObject);
        *loggedPatient += fee;
        FileHandler::updatePatient(*loggedPatient);

        for (int i = 0; i < bills.arraySize(); i++) {
            //now we make changed to bill and update it tooo
            Bill& bill = bills.getAll()[i];
            if (bill.getAppointmentID() == appointmentID) {
                bill.setStatus("cancelled");
                FileHandler::updateBill(bill);
                break;
            }
        }
        reloadAllData();
        loggedPatient = patients.findID(loggedPatient->getPatientID());
        char msg[200];
        char feeStr[50];
        customDoubleToStr(fee, feeStr, 50);
        StrCpyFunction(msg, "Appointment cancelled. PKR ");
        strcatFunction(msg, feeStr);
        strcatFunction(msg, " refunded.");
        StrCpyFunction(statusMessage, msg);
        currentScreen = Screen::PATIENT_MENU;
        appointmentIDStore[0] = '\0';
        inputStep = 0;
        inputString[0] = '\0';
        displayBuffer[0] = '\0';
    }
}

void SFMLApp::handlePayBill(sf::Event& event) {
    static char billIDStore[20] = "";

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        currentScreen = Screen::PATIENT_MENU;
        billIDStore[0] = '\0';
        inputStep = 0;
        inputString[0] = '\0';
        statusMessage[0] = '\0';
        displayBuffer[0] = '\0';
        return;
    }

    //same block of code being used as before
    if (event.type == sf::Event::TextEntered) {
        if (event.text.unicode == 8 && customStrLen(billIDStore) > 0) {
            billIDStore[customStrLen(billIDStore) - 1] = '\0';
        }
        else if (event.text.unicode >= '0' && event.text.unicode <= '9') {
            int len = customStrLen(billIDStore);
            if (len < 19) {
                billIDStore[len] = (char)event.text.unicode;
                billIDStore[len + 1] = '\0';
            }
        }
        StrCpyFunction(inputString, billIDStore);
    }
    //okkkkk agar bill unpaid : kaisai bill id , patient id kai through ham nai compare karna and apna final output
    //runs once displays all bills
    if (customStrLen(displayBuffer) == 0) {
        StrCpyFunction(displayBuffer, "Unpaid bills:\n");
        bool anyUnpaid = false;
        for (int i = 0; i < bills.arraySize(); i++) {
            Bill& bill = bills.getAll()[i];
            if (bill.getPatientID() == loggedPatient->getPatientID() && stringEqual(bill.getStatus(), "unpaid")) {
                char row[200];
                char billIDString[20];
                char appointmentIDString[20];
                char amountString[50];
                intToStrFunction(bill.getBillID(), billIDString, 20);
                intToStrFunction(bill.getAppointmentID(), appointmentIDString, 20);
                customDoubleToStr(bill.getAmount(), amountString, 50);
                StrCpyFunction(row, "Bill ID: ");
                strcatFunction(row, billIDString);
                strcatFunction(row, " | Appt: ");
                strcatFunction(row, appointmentIDString);
                strcatFunction(row, " | PKR ");
                strcatFunction(row, amountString);
                strcatFunction(row, " | ");
                strcatFunction(row, bill.getDate());
                strcatFunction(row, "\n\n");
                strcatFunction(displayBuffer, row);
                anyUnpaid = true;
            }
        }
        if (!anyUnpaid) {
            StrCpyFunction(displayBuffer, "No unpaid bills.");
        }
        strcatFunction(displayBuffer, "\nEnter Bill ID to pay:");
    }
    //if entered pressed
    //checks bill id , is it same phir kia amount hai and agar hai phir status paid kar do
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return && customStrLen(billIDStore) > 0) {
        int billID = 0;
        for (int i = 0; billIDStore[i] != '\0'; i++) {
            billID = billID * 10 + (billIDStore[i] - '0');
        }

        Bill* bill = bills.findID(billID);
        if (!bill || bill->getPatientID() != loggedPatient->getPatientID() || !stringEqual(bill->getStatus(), "unpaid")) {
            StrCpyFunction(statusMessage, "Invalid bill ID.");
            billIDStore[0] = '\0';
            inputString[0] = '\0';
            return;
        }
        if (loggedPatient->getBalance() < bill->getAmount()) {
            StrCpyFunction(statusMessage, "Insufficient funds.");
            billIDStore[0] = '\0';
            inputString[0] = '\0';
            return;
        }

        *loggedPatient -= bill->getAmount();
        bill->setStatus("paid");
        FileHandler::updateBill(*bill);
        FileHandler::updatePatient(*loggedPatient);
        reloadAllData();

        loggedPatient = patients.findID(loggedPatient->getPatientID());

        char msg[200];
        char balanceStr[50];

        customDoubleToStr(loggedPatient->getBalance(), balanceStr, 50);
        StrCpyFunction(msg, "Bill paid. Remaining balance: PKR ");
        strcatFunction(msg, balanceStr);
        StrCpyFunction(statusMessage, msg);
        currentScreen = Screen::PATIENT_MENU;
        billIDStore[0] = '\0';
        inputStep = 0;
        inputString[0] = '\0';
        displayBuffer[0] = '\0';
    }
}

//dubara jab paisai dalnain hon 
void SFMLApp::handleTopUp(sf::Event& event) {
    static char amountBuf[50] = "";

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        currentScreen = Screen::PATIENT_MENU;
        amountBuf[0] = '\0';
        inputStep = 0;
        inputString[0] = '\0';
        statusMessage[0] = '\0';
        displayBuffer[0] = '\0';
        return;
    }
    //AGAIN SAME CODE COPY KIA HAM NAI ALMOST
    if (event.type == sf::Event::TextEntered) {
        if (event.text.unicode == 8 && customStrLen(amountBuf) > 0) {
            amountBuf[customStrLen(amountBuf) - 1] = '\0';
        }
        else if ((event.text.unicode >= '0' && event.text.unicode <= '9') || event.text.unicode == '.') {
            int len = customStrLen(amountBuf);
            if (len < 49) {
                amountBuf[len] = (char)event.text.unicode;
                amountBuf[len + 1] = '\0';
            }
        }
        StrCpyFunction(inputString, amountBuf);
    }

    if (customStrLen(displayBuffer) == 0) {
        StrCpyFunction(displayBuffer, "Enter amount to add (PKR):");
    }

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return && customStrLen(amountBuf) > 0) {
        double amount = 0.0;
        bool hasDot = false;
        double decimal = 0.1;
        for (int i = 0; amountBuf[i] != '\0'; i++) {
            if (amountBuf[i] == '.') {
                hasDot = true;
            }
            else if (!hasDot) { 
                amount = amount * 10 + (amountBuf[i] - '0');
            }
            else { amount += decimal * (amountBuf[i] - '0');
            decimal *= 0.1;
            }
        }

        if (amount <= 0) {
            StrCpyFunction(statusMessage, "Amount must be greater than 0.");
            amountBuf[0] = '\0';
            inputString[0] = '\0';
            return;
        }
        //amount barhai and then wahi agai reloaded kia and showed the new balance
        *loggedPatient += amount;
        FileHandler::updatePatient(*loggedPatient);
        reloadAllData();
        loggedPatient = patients.findID(loggedPatient->getPatientID());
        char msg[200];
        char balanceStr[50];
        //basically like before jaiasai , --> copy new amount --> convert to string ==>add a message --> concatenate to statusMesssage and reset all steps etc
        customDoubleToStr(loggedPatient->getBalance(), balanceStr, 50);
        StrCpyFunction(msg, "Balance updated. New balance: PKR ");
        strcatFunction(msg, balanceStr);
        StrCpyFunction(statusMessage, msg);
        currentScreen = Screen::PATIENT_MENU;
        amountBuf[0] = '\0';
        inputStep = 0;
        inputString[0] = '\0';
        displayBuffer[0] = '\0';
    }
}

void SFMLApp::handleViewTodayAppts(sf::Event& event) {
    if (event.type == sf::Event::KeyPressed &&
        (event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::B)) {
        currentScreen = Screen::DOCTOR_MENU;
        displayBuffer[0] = '\0';
        return;
    }
    char today[11];
    getTodayDate(today);
    Appointment array[100];
    int count = 0;
    //count number of appointments to display
    if (customStrLen(displayBuffer) == 0) {
        for (int i = 0; i < appointments.arraySize(); i++) {
            Appointment& appointmenrReference = appointments.getAll()[i];
            if (appointmenrReference.getDoctorID() == loggedDoctor->getDoctorID() && stringEqual(appointmenrReference.getDate(), today)) {
                array[count++] = appointmenrReference;
            }
        }
        for (int i = 0; i < count - 1; i++) {
            for (int j = 0; j < count - i - 1; j++) {
                const char* time1 = array[j].getTimeSlot();
                const char* time2 = array[j + 1].getTimeSlot();
                int intTime1 = (time1[0] - '0') * 600 + (time1[1] - '0') * 60 + (time1[3] - '0') * 10 + (time1[4] - '0');
                int intTime2 = (time2[0] - '0') * 600 + (time2[1] - '0') * 60 + (time2[3] - '0') * 10 + (time2[4] - '0');
                if (intTime1 > intTime2) {
                    Appointment temp = array[j];
                    array[j] = array[j + 1];
                    array[j + 1] = temp;
                }
            }
        }
        if (count == 0) {
            StrCpyFunction(displayBuffer, "No appointments scheduled for today.");
            return;
        }
        StrCpyFunction(displayBuffer, "Today: ");
        strcatFunction(displayBuffer, today);
        strcatFunction(displayBuffer, "\nID | Patient ID | Slot  | Status\n\n");
        for (int i = 0; i < count; i++) {
            char row[200];
            char apptIdStr[20];
            char patientIdStr[20];
            intToStrFunction(array[i].getAppointmentID(), apptIdStr, 20);
            intToStrFunction(array[i].getPatientID(), patientIdStr, 20);
            StrCpyFunction(row, apptIdStr);
            strcatFunction(row, " | ");
            strcatFunction(row, patientIdStr);
            strcatFunction(row, " | ");
            strcatFunction(row, array[i].getTimeSlot());
            strcatFunction(row, " | ");
            strcatFunction(row, array[i].getStatus());
            strcatFunction(row, "\n \n");
            strcatFunction(displayBuffer, row);
        }
    }
}
void SFMLApp::handleMarkComplete(sf::Event& event) {
    static char appointmentIDStore[20] = "";
    //agar wahi R tou return to prev screen
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        currentScreen = Screen::DOCTOR_MENU;
        appointmentIDStore[0] = '\0';
        inputStep = 0;
        inputString[0] = '\0';
        statusMessage[0] = '\0';
        displayBuffer[0] = '\0';
        return;
    }

  
    if (event.type == sf::Event::TextEntered) {
        if (event.text.unicode == 8 && customStrLen(appointmentIDStore) > 0) {
            appointmentIDStore[customStrLen(appointmentIDStore) - 1] = '\0';
        }
        else if (event.text.unicode >= '0' && event.text.unicode <= '9') {
            int len = customStrLen(appointmentIDStore);
            if (len < 19) {
                appointmentIDStore[len] = (char)event.text.unicode;
                appointmentIDStore[len + 1] = '\0';
            }
        }
        StrCpyFunction(inputString, appointmentIDStore);
    }

    //display once the first statement
    if (customStrLen(displayBuffer) == 0) {
        char today[11];
        getTodayDate(today);
        StrCpyFunction(displayBuffer, "Today's pending appointments:\n");
        //saari display appointments jo pending
        for (int i = 0; i < appointments.arraySize(); i++) {
            Appointment& appointmentReference = appointments.getAll()[i];
            if (appointmentReference.getDoctorID() == loggedDoctor->getDoctorID() &&
                stringEqual(appointmentReference.getStatus(), "pending")) {
                char row[200];
                char appointmentIDString[20];
                char patientIDString[20];
                intToStrFunction(appointmentReference.getAppointmentID(), appointmentIDString, 20);
                intToStrFunction(appointmentReference.getPatientID(), patientIDString, 20);
                StrCpyFunction(row, "ID: ");
                strcatFunction(row, appointmentIDString);
                strcatFunction(row, " | Patient: ");
                strcatFunction(row, patientIDString);
                strcatFunction(row, " | ");
                strcatFunction(row, appointmentReference.getTimeSlot());
                strcatFunction(row, "\n\n");
                strcatFunction(displayBuffer, row);
            }
        }
        strcatFunction(displayBuffer, "\nEnter Appointment ID:");
    }

    //
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return && customStrLen(appointmentIDStore) > 0) {
        int appointmentID = 0;
        for (int i = 0; appointmentIDStore[i] != '\0'; i++) {
            appointmentID = appointmentID * 10 + (appointmentIDStore[i] - '0');
        }
        char today[11];
        getTodayDate(today);
        Appointment* appointmentPointer = appointments.findID(appointmentID);
        if (!appointmentPointer || appointmentPointer->getDoctorID() != loggedDoctor->getDoctorID() ||
            !stringEqual(appointmentPointer->getStatus(), "pending")) {
            StrCpyFunction(statusMessage, "Invalid appointment ID.");
            appointmentIDStore[0] = '\0';
            inputString[0] = '\0';
            return;
        }
        appointmentPointer->setStatus("completed");
        FileHandler::updateAppointment(*appointmentPointer);
        reloadAllData();
        loggedDoctor = doctors.findID(loggedDoctor->getDoctorID());
        StrCpyFunction(statusMessage, "Appointment marked as completed.");
        currentScreen = Screen::DOCTOR_MENU;
        appointmentIDStore[0] = '\0';
        inputStep = 0;
        inputString[0] = '\0';
        displayBuffer[0] = '\0';
    }
}

void SFMLApp::handleAddPatient(sf::Event& event) {
    static char nameStore[100] = "";
    static char ageStore[10] = "";
    static char genderStore[5] = "";
    static char contactStore[20] = "";
    static char passwordStore[100] = "";
    static char balanceStore[50] = "";

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        currentScreen = Screen::ADMIN_MENU;
        nameStore[0] = ageStore[0] = genderStore[0] = contactStore[0] = passwordStore[0] = balanceStore[0] = '\0';
        inputStep = 0;
        inputString[0] = '\0';
        statusMessage[0] = '\0';
        isPasswordField = false;
        displayBuffer[0] = '\0';
        return;
    }

    char* currentField = nullptr;
    if (inputStep == 0) { 
        currentField = nameStore; 
        isPasswordField = false;
    }
    else if (inputStep == 1) { 
        currentField = ageStore;
    }
    else if (inputStep == 2) {
        currentField = genderStore; 
    }
    else if (inputStep == 3) {
        currentField = contactStore; 
    }
    else if (inputStep == 4) {
        currentField = passwordStore;
        isPasswordField = true;
    }
    else if (inputStep == 5) {
        currentField = balanceStore; 
        isPasswordField = false;
    }

    if (currentField && event.type == sf::Event::TextEntered) {
        if (event.text.unicode == 8 && customStrLen(currentField) > 0) {
            currentField[customStrLen(currentField) - 1] = '\0';
        }
        else if (event.text.unicode >= 32 && event.text.unicode < 127) {
            int len = customStrLen(currentField);
            if (len < 99) {
                currentField[len] = (char)event.text.unicode;
                currentField[len + 1] = '\0';
            }
        }
        StrCpyFunction(inputString, currentField);
    }

    if (customStrLen(displayBuffer) == 0) {
        if (inputStep == 0) {
            StrCpyFunction(displayBuffer, "Enter patient full name (max 50 chars):");
        }
        else if (inputStep == 1) { 
            StrCpyFunction(displayBuffer, "Enter age:");
        }
        else if (inputStep == 2) {
            StrCpyFunction(displayBuffer, "Enter gender (M/F):");
        }
        else if (inputStep == 3) {
            StrCpyFunction(displayBuffer, "Enter contact (11 digits):");
        }
        else if (inputStep == 4) { 
            StrCpyFunction(displayBuffer, "Enter password (min 6 chars):");
        }
        else if (inputStep == 5) { 
            StrCpyFunction(displayBuffer, "Enter initial balance (PKR):");
        }
    }

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return) {
        statusMessage[0] = '\0';

        if (inputStep == 0) {
            if (customStrLen(nameStore) == 0 || customStrLen(nameStore) > 50) {
                StrCpyFunction(statusMessage, "Name must be 1-50 chars.");
                return;
            }
            StrCpyFunction(displayBuffer, "Enter age:");
            inputStep = 1;
            ageStore[0] = '\0';
            inputString[0] = '\0';
        }
        else if (inputStep == 1) {
            bool valid = (customStrLen(ageStore) > 0);
            for (int i = 0; ageStore[i] != '\0'; i++) {
                if (ageStore[i] < '0' || ageStore[i] > '9') { valid = false; break; }
            }
            if (!valid) {
                StrCpyFunction(statusMessage, "Enter a valid age.");
                return; 
            }
            StrCpyFunction(displayBuffer, "Enter gender (M/F):");
            inputStep = 2;
            genderStore[0] = '\0';
            inputString[0] = '\0';
        }
        else if (inputStep == 2) {
            if ((genderStore[0] != 'M' && genderStore[0] != 'F' &&
                genderStore[0] != 'm' && genderStore[0] != 'f') ||
                customStrLen(genderStore) != 1) {
                StrCpyFunction(statusMessage, "Gender must be M or F.");
                return;
            }
            StrCpyFunction(displayBuffer, "Enter contact (11 digits):");
            inputStep = 3;
            contactStore[0] = '\0';
            inputString[0] = '\0';
        }
        else if (inputStep == 3) {
            char contactArray[12];
            copyToStore(contactArray, contactStore, 12);
            if (!Validator::isValidContact(contactArray)) {
                StrCpyFunction(statusMessage, "Contact must be exactly 11 digits.");
                contactStore[0] = '\0';
                inputString[0] = '\0';
                return;
            }
            StrCpyFunction(displayBuffer, "Enter password (min 6 chars):");
            inputStep = 4;
            passwordStore[0] = '\0';
            inputString[0] = '\0';
        }
        else if (inputStep == 4) {
            char passArray[51];
            copyToStore(passArray, passwordStore, 51);
            if (!Validator::isValidPassword(passArray)) {
                StrCpyFunction(statusMessage, "Password must be at least 6 chars.");
                passwordStore[0] = '\0';
                inputString[0] = '\0';
                return;
            }
            StrCpyFunction(displayBuffer, "Enter initial balance (PKR):");
            inputStep = 5;
            balanceStore[0] = '\0';
            inputString[0] = '\0';
            isPasswordField = false;
        }
        else if (inputStep == 5) {
            bool valid = (customStrLen(balanceStore) > 0);
            for (int i = 0; balanceStore[i] != '\0'; i++) {
                if (balanceStore[i] != '.' && (balanceStore[i] < '0' || balanceStore[i] > '9')) {
                    valid = false; break;
                }
            }
            if (!valid) { 
                StrCpyFunction(statusMessage, "Enter a valid balance.");
                return;
            }

            double balance = 0.0;
            bool hasDot = false;
            double decimal = 0.1;
            for (int i = 0; balanceStore[i] != '\0'; i++) {
                if (balanceStore[i] == '.') {
                    hasDot = true; 
                }
                else if (!hasDot) { 
                    balance = balance * 10 + (balanceStore[i] - '0');
                }
                else { 
                    balance += decimal * (balanceStore[i] - '0'); 
                    decimal *= 0.1; 
                }
            }

            int age = 0;
            for (int i = 0; ageStore[i] != '\0'; i++) {
                age = age * 10 + (ageStore[i] - '0');
            }
            char gender;
            if (genderStore[0] == 'm') {
                gender = 'M';
            }
            else if (genderStore[0] == 'f') {
                gender = 'F';
            }
            else {
                gender = genderStore[0];
            }

            int newID = FileHandler::getFilePatientID();
            Patient newPatient(newID, nameStore, passwordStore, false, balance, gender, age, contactStore, 0);
            FileHandler::appendPatient(newPatient);
            reloadAllData();

            char msg[200];
            StrCpyFunction(msg, "Patient added successfully. ID: ");
            char IDString[20];
            intToStrFunction(newID, IDString, 20);
            strcatFunction(msg, IDString);
            StrCpyFunction(statusMessage, msg);

            currentScreen = Screen::ADMIN_MENU;
            nameStore[0] = ageStore[0] = genderStore[0] = contactStore[0] = passwordStore[0] = balanceStore[0] = '\0';
            inputStep = 0;
            inputString[0] = '\0';
            displayBuffer[0] = '\0';
            isPasswordField = false;
        }
    }
}

void SFMLApp::handleRemovePatient(sf::Event& event) {
    static char patientIDStore[20] = "";

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        currentScreen = Screen::ADMIN_MENU;
        patientIDStore[0] = '\0';
        inputStep = 0;
        inputString[0] = '\0';
        statusMessage[0] = '\0';
        displayBuffer[0] = '\0';
        return;
    }

    if (event.type == sf::Event::TextEntered) {
        if (event.text.unicode == 8 && customStrLen(patientIDStore) > 0) {
            patientIDStore[customStrLen(patientIDStore) - 1] = '\0';
        }
        else if (event.text.unicode >= '0' && event.text.unicode <= '9') {
            int len = customStrLen(patientIDStore);
            if (len < 19) {
                patientIDStore[len] = (char)event.text.unicode;
                patientIDStore[len + 1] = '\0';
            }
        }
        StrCpyFunction(inputString, patientIDStore);
    }

    if (customStrLen(displayBuffer) == 0) {
        StrCpyFunction(displayBuffer, "Patients:\n");
        for (int i = 0; i < patients.arraySize(); i++) {
            Patient& p = patients.getAll()[i];
            char row[300];
            char IDString[20];
            char ageString[10];
            intToStrFunction(p.getPatientID(), IDString, 20);
            intToStrFunction(p.getAge(), ageString, 10);
            StrCpyFunction(row, "ID: ");
            strcatFunction(row, IDString);
            strcatFunction(row, " | ");
            strcatFunction(row, p.getName());
            strcatFunction(row, " | Age: ");
            strcatFunction(row, ageString);
            strcatFunction(row, " | ");
            char genderString[2] = { p.getGender(), '\0' };
            strcatFunction(row, genderString);
            strcatFunction(row, "\n\n");
            strcatFunction(displayBuffer, row);
        }
        if (patients.arraySize() == 0) {
            strcatFunction(displayBuffer, "No patients registered.\n");
        }
        strcatFunction(displayBuffer, "\nEnter Patient ID to remove:");
    }

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return && customStrLen(patientIDStore) > 0) {
        int patientID = 0;
        for (int i = 0; patientIDStore[i] != '\0'; i++) {
            patientID = patientID * 10 + (patientIDStore[i] - '0');
        }

        Patient* patient = patients.findID(patientID);
        if (!patient) {
            StrCpyFunction(statusMessage, "Patient not found.");
            patientIDStore[0] = '\0';
            inputString[0] = '\0';
            return;
        }

        for (int i = 0; i < bills.arraySize(); i++) {
            Bill& bill = bills.getAll()[i];
            if (bill.getPatientID() == patientID && stringEqual(bill.getStatus(), "unpaid")) {
                StrCpyFunction(statusMessage, "Cannot remove patient with unpaid bills.");
                patientIDStore[0] = '\0';
                inputString[0] = '\0';
                return;
            }
        }

        for (int i = 0; i < appointments.arraySize(); i++) {
            Appointment& ap = appointments.getAll()[i];
            if (ap.getPatientID() == patientID && stringEqual(ap.getStatus(), "pending")) {
                StrCpyFunction(statusMessage, "Cannot remove patient with pending appointments.");
                patientIDStore[0] = '\0';
                inputString[0] = '\0';
                return;
            }
        }

        FileHandler::deletePatient(patientID);
        reloadAllData();
        StrCpyFunction(statusMessage, "Patient removed successfully.");
        currentScreen = Screen::ADMIN_MENU;
        patientIDStore[0] = '\0';
        inputStep = 0;
        inputString[0] = '\0';
        displayBuffer[0] = '\0';
    }
}
//litereally same logic but different showing as handleMarkShow
void SFMLApp::handleMarkNoShow(sf::Event& e) {
    static char appointmentIDStore[20] = "";

    if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape) {
        currentScreen = Screen::DOCTOR_MENU;
        appointmentIDStore[0] = '\0';
        inputStep = 0;
        inputString[0] = '\0';
        statusMessage[0] = '\0';
        displayBuffer[0] = '\0';
        return;
    }
    if (e.type == sf::Event::TextEntered) {
        if (e.text.unicode == 8 && customStrLen(appointmentIDStore) > 0) {
            appointmentIDStore[customStrLen(appointmentIDStore) - 1] = '\0';
        }
        else if (e.text.unicode >= '0' && e.text.unicode <= '9') {
            int len = customStrLen(appointmentIDStore);
            if (len < 19) {
                appointmentIDStore[len] = (char)e.text.unicode;
                appointmentIDStore[len + 1] = '\0';
            }
        }
        StrCpyFunction(inputString, appointmentIDStore);
    }

    if (customStrLen(displayBuffer) == 0) {
        char today[11];
        getTodayDate(today);
        StrCpyFunction(displayBuffer, "Today's pending appointments:\n");
        for (int i = 0; i < appointments.arraySize(); i++) {
            Appointment& appointmentReference = appointments.getAll()[i];
            if (appointmentReference.getDoctorID() == loggedDoctor->getDoctorID() &&
                stringEqual(appointmentReference.getStatus(), "pending")) {
                char row[200];
                char appointmentIDString[20];
                char patientIDString[20];
                intToStrFunction(appointmentReference.getAppointmentID(), appointmentIDString, 20);
                intToStrFunction(appointmentReference.getPatientID(), patientIDString, 20);
                StrCpyFunction(row, "ID: ");
                strcatFunction(row, appointmentIDString);
                strcatFunction(row, " | Patient: ");
                strcatFunction(row, patientIDString);
                strcatFunction(row, " | ");
                strcatFunction(row, appointmentReference.getTimeSlot());
                strcatFunction(row, "\n\n");
                strcatFunction(displayBuffer, row);
            }
        }
        strcatFunction(displayBuffer, "\nEnter Appointment ID:");
    }

    if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Return && customStrLen(appointmentIDStore) > 0) {
        int appointmentID = 0;
        for (int i = 0; appointmentIDStore[i] != '\0'; i++) {
            appointmentID = appointmentID * 10 + (appointmentIDStore[i] - '0');
        }
        char today[11];
        getTodayDate(today);
        Appointment* appointmentPointer = appointments.findID(appointmentID);
        if (!appointmentPointer || appointmentPointer->getDoctorID() != loggedDoctor->getDoctorID() ||
            !stringEqual(appointmentPointer->getStatus(), "pending")) {
            StrCpyFunction(statusMessage, "Invalid appointment ID.");
            appointmentIDStore[0] = '\0';
            inputString[0] = '\0';
            return;
        }
        appointmentPointer->setStatus("no show");
        FileHandler::updateAppointment(*appointmentPointer);
        for (int i = 0; i < bills.arraySize(); i++) {
            Bill& bill = bills.getAll()[i];
            if (bill.getAppointmentID() == appointmentID) {
                bill.setStatus("cancelled");
                FileHandler::updateBill(bill);
                break;
            }
        }
        reloadAllData();
        loggedDoctor = doctors.findID(loggedDoctor->getDoctorID());
        StrCpyFunction(statusMessage, "Appointment marked as no-show.");
        currentScreen = Screen::DOCTOR_MENU;
        appointmentIDStore[0] = '\0';
        inputStep = 0;
        inputString[0] = '\0';
        displayBuffer[0] = '\0';
    }
}

void SFMLApp::handleWritePrescription(sf::Event& event) {
    static char appointmentStore[20] = "";
    static char medicineStore[500] = "";
    static char notesStore[300] = "";

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        currentScreen = Screen::DOCTOR_MENU;
        appointmentStore[0] = medicineStore[0] = notesStore[0] = '\0';
        inputStep = 0;
        inputString[0] = '\0';
        statusMessage[0] = '\0';
        displayBuffer[0] = '\0';
        return;
    }

    char* currentField = nullptr;
    //pointing to the requires storage unit
    if (inputStep == 0) { 
        currentField = appointmentStore; 
    }
    else if (inputStep == 1) { 
        currentField = medicineStore;
    }
    else if (inputStep == 2) {
        currentField = notesStore;
    }

    if (currentField && event.type == sf::Event::TextEntered) {
        if (event.text.unicode == 8 && customStrLen(currentField) > 0) {
            currentField[customStrLen(currentField) - 1] = '\0';
        }
        else if (event.text.unicode >= 32 && event.text.unicode < 127) {
            int len = customStrLen(currentField);
            if (len < 499) {
                currentField[len] = (char)event.text.unicode;
                currentField[len + 1] = '\0';
            }
        }
        StrCpyFunction(inputString, currentField);
    }

    if (customStrLen(displayBuffer) == 0) {
        if (inputStep == 0) { 
            StrCpyFunction(displayBuffer, "Enter Appointment ID (must be completed):");
        }
        else if (inputStep == 1) { 
            StrCpyFunction(displayBuffer, "Enter medicines (e.g. Paracetamol 500mg):");
        }
        else if (inputStep == 2){
            StrCpyFunction(displayBuffer, "Enter notes:");
        }
    }

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return) {
        if (inputStep == 0) {
            int appointmentID = 0;
            for (int i = 0; appointmentStore[i] != '\0'; i++) {
                appointmentID = appointmentID * 10 + (appointmentStore[i] - '0');
            }
            Appointment* appointmentPointer = appointments.findID(appointmentID);
            //basically we checking whether the appointmet is completed for writing prescription
            if (!appointmentPointer || appointmentPointer->getDoctorID() != loggedDoctor->getDoctorID() || !stringEqual(appointmentPointer->getStatus(), "completed")) {
                StrCpyFunction(statusMessage, "Invalid or not completed appointment.");
                appointmentStore[0] = '\0';
                inputString[0] = '\0';
                return;
            }
            
            for (int i = 0; i < prescriptions.arraySize(); i++) {
                //we then check if prescription has already been written or not
                if (prescriptions.getAll()[i].getappointmentID() == appointmentID) {
                    StrCpyFunction(statusMessage, "Prescription already written for this appointment.");
                    currentScreen = Screen::DOCTOR_MENU;
                    appointmentStore[0] = medicineStore[0] = notesStore[0] = '\0';
                    inputStep = 0;
                    inputString[0] = '\0';
                    displayBuffer[0] = '\0';
                    return;
                }
            }
            StrCpyFunction(statusMessage, "Enter medicines (e.g. Paracetamol 500mg;Amoxicillin 250mg):");
            inputStep = 1;
            medicineStore[0] = '\0';
            inputString[0] = '\0';
        }
        //if we are writing medicine
        else if (inputStep == 1) {
            if (customStrLen(medicineStore) > 499) {
                medicineStore[499] = '\0';
            }
            StrCpyFunction(statusMessage, "Enter notes (max 300 chars):");
            inputStep = 2;
            notesStore[0] = '\0';
            inputString[0] = '\0';
        }
        else if (inputStep == 2) {
            if (customStrLen(notesStore) > 299) {
                notesStore[299] = '\0';
            }

            int appointmentID = 0;
            for (int i = 0; appointmentStore[i] != '\0'; i++) {
                appointmentID = appointmentID * 10 + (appointmentStore[i] - '0');
            }
            //again find appointment based on id
            //write prescription and append
            //reload data and aftr changing screen again resotre the static back to intial state as we need to since they are not deleted naaa

            Appointment* appointmentPointer = appointments.findID(appointmentID);
            int prescriptionID = FileHandler::getFilePrescriptionID();
            Prescription newPrescription(prescriptionID, appointmentID, appointmentPointer->getPatientID(),
                loggedDoctor->getDoctorID(), appointmentPointer->getDate(),
                medicineStore, notesStore);
            FileHandler::appendPrescription(newPrescription);
            reloadAllData();
            loggedDoctor = doctors.findID(loggedDoctor->getDoctorID());
            StrCpyFunction(statusMessage, "Prescription saved.");
            currentScreen = Screen::DOCTOR_MENU;
            appointmentStore[0] = medicineStore[0] = notesStore[0] = '\0';
            inputStep = 0;
            inputString[0] = '\0';
            displayBuffer[0] = '\0';
        }
    }
}

void SFMLApp::handleViewPatientHistory(sf::Event& event) {
    static char patientStore[20] = "";

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        currentScreen = Screen::DOCTOR_MENU;
        patientStore[0] = '\0';
        inputStep = 0;
        inputString[0] = '\0';
        statusMessage[0] = '\0';
        displayBuffer[0] = '\0';
        return;
    }

    if (inputStep == 0) {
        if (event.type == sf::Event::TextEntered) {
            if (event.text.unicode == 8 && customStrLen(patientStore) > 0) {
                patientStore[customStrLen(patientStore) - 1] = '\0';
            }
            else if (event.text.unicode >= '0' && event.text.unicode <= '9') {
                int len = customStrLen(patientStore);
                if (len < 19) {
                    patientStore[len] = (char)event.text.unicode;
                    patientStore[len + 1] = '\0';
                }
            }
            StrCpyFunction(inputString, patientStore);
        }
        if (customStrLen(displayBuffer) == 0) {
            StrCpyFunction(displayBuffer, "Enter Patient ID:");
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return && customStrLen(patientStore) > 0) {
            int patientID = 0;
            //converting patientID from string to required
            for (int i = 0; patientStore[i] != '\0'; i++) {
                patientID = patientID * 10 + (patientStore[i] - '0');
            }
            //finding id 
            Patient* patient = patients.findID(patientID);
            bool hasCompleted = false;
            for (int i = 0; i < appointments.arraySize(); i++) {
                Appointment& appointmentReference = appointments.getAll()[i];
                if (appointmentReference.getPatientID() == patientID &&
                    appointmentReference.getDoctorID() == loggedDoctor->getDoctorID() &&
                    stringEqual(appointmentReference.getStatus(), "completed")) {
                    hasCompleted = true;
                    break;
                }
            }
            //basically if patient does not exist or doctor i trying to acess someone else histroy
            if (!patient || !hasCompleted) {
                StrCpyFunction(statusMessage, "Access denied. You can only view records of your own patients.");
                patientStore[0] = '\0';
                inputString[0] = '\0';
                return;
            }

            Prescription array[100];
            int count = 0;
            //finds the prescriptions written regarding patient
            for (int i = 0; i < prescriptions.arraySize(); i++) {
                Prescription& prescriptionReference = prescriptions.getAll()[i];
                if (prescriptionReference.getpatientID() == patientID && prescriptionReference.getdoctorID() == loggedDoctor->getDoctorID()) {
                    array[count++] = prescriptionReference;
                }
            }

            sortPrescriptionsByDate(array, count, true);
            char header[200];
            StrCpyFunction(header, "Medical history for Patient ");
            char patientIdStr[20];
            intToStrFunction(patientID, patientIdStr, 20);
            strcatFunction(header, patientIdStr);
            strcatFunction(header, ":\n\n");
            StrCpyFunction(displayBuffer, header);
            for (int i = 0; i < count; i++) {
                char row[500];
                StrCpyFunction(row, array[i].getDate());
                strcatFunction(row, " | ");
                strcatFunction(row, array[i].getMedicine());
                strcatFunction(row, " | ");
                strcatFunction(row, array[i].getNotes());
                strcatFunction(row, "\n");
                strcatFunction(displayBuffer, row);
            }
            if (count == 0) {
                strcatFunction(displayBuffer, "No prescriptions found.\n");
            }
            inputStep = 1;
        }
    }
}

//okkk patient and doctor same logic
//first check if like escape wala
//agar nhi then create reference the the req storage 
// put all in the required storages and then just write
void SFMLApp::handleViewAllPatients(sf::Event& event) {
    //returning back
    if (event.type == sf::Event::KeyPressed &&
        (event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::B)) {
        currentScreen = Screen::ADMIN_MENU;
        displayBuffer[0] = '\0';
        return;
    }
    if (customStrLen(displayBuffer) == 0) {
        StrCpyFunction(displayBuffer, "ID | Name | Age | Gender | Contact | Balance | Unpaid\n");
        for (int i = 0; i < patients.arraySize(); i++) {
            Patient& patientReference = patients.getAll()[i];
            char row[500];
            char IDString[20];
            char ageString[10];
            char balanceString[50];
            char unpaidString[10];

            intToStrFunction(patientReference.getPatientID(), IDString, 20);
            intToStrFunction(patientReference.getAge(), ageString, 10);
            customDoubleToStr(patientReference.getBalance(), balanceString, 50);
            intToStrFunction(countUnpaidBills(patientReference.getPatientID()), unpaidString, 10);

            StrCpyFunction(row, IDString);
            strcatFunction(row, " | ");
            strcatFunction(row, patientReference.getName());
            strcatFunction(row, " | ");
            strcatFunction(row, ageString);
            strcatFunction(row, " | ");
            char genderStr[2] = { patientReference.getGender(), '\0' };
            strcatFunction(row, genderStr);
            strcatFunction(row, " | ");
            strcatFunction(row, patientReference.getPhoneNumber());
            strcatFunction(row, " | PKR ");
            strcatFunction(row, balanceString);
            strcatFunction(row, " | ");
            strcatFunction(row, unpaidString);
            strcatFunction(row, "\n\n");
            strcatFunction(displayBuffer, row);
        }

        if (patients.arraySize() == 0) {
            strcatFunction(displayBuffer, "No patients registered.\n");
        }
    }
}

void SFMLApp::handleViewAllDoctors(sf::Event& event) {
    if (event.type == sf::Event::KeyPressed &&
        (event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::B)) {
        currentScreen = Screen::ADMIN_MENU;
        displayBuffer[0] = '\0';
        return;
    }
    if (customStrLen(displayBuffer) == 0) {
        StrCpyFunction(displayBuffer, "ID | Name | Specialization | Contact | Fee\n");
        for (int i = 0; i < doctors.arraySize(); i++) {
            Doctor& doctorReferece = doctors.getAll()[i];
            char row[500];
            char IDString[20];
            char feeString[50];
            intToStrFunction(doctorReferece.getDoctorID(), IDString, 20);
            customDoubleToStr(doctorReferece.getFee(), feeString, 50);
            StrCpyFunction(row, IDString);
            strcatFunction(row, " | ");
            strcatFunction(row, doctorReferece.getName());
            strcatFunction(row, " | ");
            strcatFunction(row, doctorReferece.getSpecialization());
            strcatFunction(row, " | ");
            strcatFunction(row, doctorReferece.getContactNumber());
            strcatFunction(row, " | PKR ");
            strcatFunction(row, feeString);
            strcatFunction(row, "\n\n");
            strcatFunction(displayBuffer, row);
        }
        if (doctors.arraySize() == 0) {
            strcatFunction(displayBuffer, "No doctors registered.\n");
        }
    }
}
//same logic we apply here
void SFMLApp::handleViewAllAppointments(sf::Event& e) {
    if (e.type == sf::Event::KeyPressed &&
        (e.key.code == sf::Keyboard::Escape || e.key.code == sf::Keyboard::B)) {
        currentScreen = Screen::ADMIN_MENU;
        displayBuffer[0] = '\0';
        return;
    }
    if (customStrLen(displayBuffer) == 0) {
        Appointment array[100];
        int count = appointments.arraySize();
        for (int i = 0; i < count; i++) {
            array[i] = appointments.getAll()[i];
        }
        sortAppointmentsByDate(array, count, false);
        StrCpyFunction(displayBuffer, "ID | Patient | Doctor | Date  Slot | Status\n\n");
        for (int i = 0; i < count; i++) {
            char row[200];
            char apointmentIDString[20];
            char patientIDString[20];
            char doctorIDString[20];
            intToStrFunction(array[i].getAppointmentID(), apointmentIDString, 20);
            intToStrFunction(array[i].getPatientID(), patientIDString, 20);
            intToStrFunction(array[i].getDoctorID(), doctorIDString, 20);
            StrCpyFunction(row, apointmentIDString);
            strcatFunction(row, " | ");
            strcatFunction(row, patientIDString);
            strcatFunction(row, " | ");
            strcatFunction(row, doctorIDString);
            strcatFunction(row, " | ");
            strcatFunction(row, array[i].getDate());
            strcatFunction(row, " | ");
            strcatFunction(row, array[i].getTimeSlot());
            strcatFunction(row, " | ");
            strcatFunction(row, array[i].getStatus());
            strcatFunction(row, "\n\n");
            strcatFunction(displayBuffer, row);
        }
        if (count == 0) {
            strcatFunction(displayBuffer, "No appointments.\n");
        }
    }
}
//same logic here
void SFMLApp::handleViewUnpaidBills(sf::Event& e) {
    if (e.type == sf::Event::KeyPressed &&
        (e.key.code == sf::Keyboard::Escape || e.key.code == sf::Keyboard::B)) {
        currentScreen = Screen::ADMIN_MENU;
        displayBuffer[0] = '\0';
        return;
    }
    if (customStrLen(displayBuffer) == 0) {
        StrCpyFunction(displayBuffer, "Bill ID | Patient ID | Amount | Date\n\n");
        bool anyUnpaid = false;
        for (int i = 0; i < bills.arraySize(); i++) {
            Bill& bill = bills.getAll()[i];
            if (stringEqual(bill.getStatus(), "unpaid")) {
                char row[200];
                char billIDString[20];
                char patientIDString[20];
                char amountString[50];
                intToStrFunction(bill.getBillID(), billIDString, 20);
                intToStrFunction(bill.getPatientID(), patientIDString, 20);
                customDoubleToStr(bill.getAmount(), amountString, 50);
                StrCpyFunction(row, billIDString);
                strcatFunction(row, " | ");
                strcatFunction(row, patientIDString);
                strcatFunction(row, " | PKR ");
                strcatFunction(row, amountString);
                strcatFunction(row, " | ");
                strcatFunction(row, bill.getDate());
                if (dateIsOverdue(bill.getDate())) {
                    strcatFunction(row, " [OVERDUE]");
                }
                strcatFunction(row, "\n\n");
                strcatFunction(displayBuffer, row);
                anyUnpaid = true;
            }
        }
        if (!anyUnpaid) {
            strcatFunction(displayBuffer, "No unpaid bills.\n");
        }
    }
}


void SFMLApp::handleViewSecurityLog(sf::Event& event) {
    //wahi if esc --> back
    if (event.type == sf::Event::KeyPressed &&
        (event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::B)) {
        currentScreen = Screen::ADMIN_MENU;
        displayBuffer[0] = '\0';
        return;
    }
    //reading security log ,if no exist , no fiund else read and put in display buffer
    if (customStrLen(displayBuffer) == 0) {
        std::ifstream logFile("security_log.txt");
        if (!logFile.is_open()) {
            StrCpyFunction(displayBuffer, "No security events logged.");
            return;
        }
        char line[300];
        bool hasEvents = false;
        while (logFile.getline(line, 300)) {
            if (line[0] != '\0') {
                strcatFunction(displayBuffer, line);
                strcatFunction(displayBuffer, "\n");
                hasEvents = true;
            }
        }
        if (!hasEvents) {
            StrCpyFunction(displayBuffer, "No security events logged.");
        }
        logFile.close();
    }
}

void SFMLApp::handleAddDoctor(sf::Event& event) {
    static char nameStore[100] = "";
    static char specializationStore[100] = "";
    static char contactStore[20] = "";
    static char passwordStore[100] = "";
    static char feeStore[50] = "";

   
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        currentScreen = Screen::ADMIN_MENU;
        nameStore[0] = specializationStore[0] = contactStore[0] = passwordStore[0] = feeStore[0] = '\0';
        inputStep = 0;
        inputString[0] = '\0';
        statusMessage[0] = '\0';
        isPasswordField = false;
        displayBuffer[0] = '\0';
        return;
    }

    //same based on steps we decide what to show
    char* currentField = nullptr;
    if (inputStep == 0) { 
        currentField = nameStore;
        isPasswordField = false;
    }
    else if (inputStep == 1) { 
        currentField = specializationStore;
    }
    else if (inputStep == 2) {
        currentField = contactStore;
    }
    else if (inputStep == 3) { 
        currentField = passwordStore; 
        isPasswordField = true; 
    }
    else if (inputStep == 4) { 
        currentField = feeStore;   
        isPasswordField = false; }

    if (currentField && event.type == sf::Event::TextEntered) {
        if (event.text.unicode == 8 && customStrLen(currentField) > 0) {
            currentField[customStrLen(currentField) - 1] = '\0';
        }
        else if (event.text.unicode >= 32 && event.text.unicode < 127) {
            int len = customStrLen(currentField);
            if (len < 99) {
                currentField[len] = (char)event.text.unicode;
                currentField[len + 1] = '\0';
            }
        }
        StrCpyFunction(inputString, currentField);
    }

    if (customStrLen(displayBuffer) == 0) {
        if (inputStep == 0) { 
            StrCpyFunction(displayBuffer, "Enter doctor name:"); 
        }
        else if (inputStep == 1) {
            StrCpyFunction(displayBuffer, "Enter specialization:"); 
        }
        else if (inputStep == 2) {
            StrCpyFunction(displayBuffer, "Enter contact (11 digits):");
        }
        else if (inputStep == 3) {
            StrCpyFunction(displayBuffer, "Enter password (min 6 chars):");
        }
        else if (inputStep == 4) {
            StrCpyFunction(displayBuffer, "Enter fee (PKR):"); 
        }
    }

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return) {
        statusMessage[0] = '\0';
        if (inputStep == 0) {
            //ensuring name bw 0 and 50 char
            if (customStrLen(nameStore) == 0 || customStrLen(nameStore) > 50) {
                StrCpyFunction(statusMessage, "Name must be 1-50 chars.");
                return;
            }
            //moving to next step
            StrCpyFunction(displayBuffer, "Enter specialization:");
            inputStep = 1;
            specializationStore[0] = '\0';
            inputString[0] = '\0';
        }
        else if (inputStep == 1) {
            // again validation for specialization 
            if (customStrLen(specializationStore) == 0 || customStrLen(specializationStore) > 50) {
                StrCpyFunction(statusMessage, "Specialization must be 1-50 chars.");
                return;
            }
            StrCpyFunction(displayBuffer, "Enter contact (11 digits):");
            inputStep = 2;
            contactStore[0] = '\0';
            inputString[0] = '\0';
        }
        else if (inputStep == 2) {
            char contactArray[12];
            copyToStore(contactArray, contactStore, 12);
            //validating contanct
            if (!Validator::isValidContact(contactArray)) {
                StrCpyFunction(statusMessage, "Contact must be exactly 11 digits.");
                contactStore[0] = '\0';
                inputString[0] = '\0';
                return;
            }
            StrCpyFunction(displayBuffer, "Enter password (min 6 chars):");
            inputStep = 3;
            passwordStore[0] = '\0';
            inputString[0] = '\0';
        }
        else if (inputStep == 3) {
            char passwordArray[51];
            //doing the same for password
            copyToStore(passwordArray, passwordStore, 51);
            if (!Validator::isValidPassword(passwordArray)) {
                StrCpyFunction(statusMessage, "Password must be at least 6 chars.");
                passwordStore[0] = '\0';
                inputString[0] = '\0';
                return;
            }
            StrCpyFunction(displayBuffer, "Enter consultation fee (PKR):");
            inputStep = 4;
            feeStore[0] = '\0';
            inputString[0] = '\0';
            isPasswordField = false;
        }
        else if (inputStep == 4) {
            double fee = 0.0;
            bool hasDot = false;
            double decimal = 0.1;
            //same code for fee doubel form storing
            for (int i = 0; feeStore[i] != '\0'; i++) {
                if (feeStore[i] == '.') {
                    hasDot = true; 
                }
                else if (!hasDot) { 
                    fee = fee * 10 + (feeStore[i] - '0');
                }
                else { 
                    fee += decimal * (feeStore[i] - '0'); decimal *= 0.1; 
                }
            }
            if (!Validator::isValidPositiveAmount(fee)) {
                StrCpyFunction(statusMessage, "Fee must be a positive number.");
                feeStore[0] = '\0';
                inputString[0] = '\0';
                return;
            }
           
            int newID = FileHandler::getFileDoctorID();
            Doctor newDoctor(newID, nameStore, passwordStore, specializationStore, contactStore, fee, false);
            FileHandler::appendDoctor(newDoctor);
            reloadAllData();
            char msg[200];

            StrCpyFunction(msg, "Doctor added successfully. ID: ");
            char IDString[20];
            intToStrFunction(newID, IDString, 20);
            strcatFunction(msg, IDString);

            StrCpyFunction(statusMessage, msg);
            currentScreen = Screen::ADMIN_MENU;
            nameStore[0] = specializationStore[0] = contactStore[0] = passwordStore[0] = feeStore[0] = '\0';
            inputStep = 0;
            inputString[0] = '\0';
            displayBuffer[0] = '\0';
            isPasswordField = false;
        }
    }
}

void SFMLApp::handleRemoveDoctor(sf::Event& event) {
    static char doctorIDStore[20] = "";

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        currentScreen = Screen::ADMIN_MENU;
        doctorIDStore[0] = '\0';
        inputStep = 0;
        inputString[0] = '\0';
        statusMessage[0] = '\0';
        displayBuffer[0] = '\0';
        return;
    }
    if (event.type == sf::Event::TextEntered) {
        if (event.text.unicode == 8 && customStrLen(doctorIDStore) > 0) {
            doctorIDStore[customStrLen(doctorIDStore) - 1] = '\0';
        }
        else if (event.text.unicode >= '0' && event.text.unicode <= '9') {
            int len = customStrLen(doctorIDStore);
            if (len < 19) {
                doctorIDStore[len] = (char)event.text.unicode;
                doctorIDStore[len + 1] = '\0';
            }
        }
        StrCpyFunction(inputString, doctorIDStore);
    }

    if (customStrLen(displayBuffer) == 0) {
        StrCpyFunction(displayBuffer, "Doctors:\n");

        for (int i = 0; i < doctors.arraySize(); i++) {
            Doctor& doctorReference = doctors.getAll()[i];
            char row[200];
            char idString[20];
            char feeString[50];
            intToStrFunction(doctorReference.getDoctorID(), idString, 20);
            customDoubleToStr(doctorReference.getFee(), feeString, 50);
            StrCpyFunction(row, "ID: ");
            strcatFunction(row, idString);
            strcatFunction(row, " | ");
            strcatFunction(row, doctorReference.getName());
            strcatFunction(row, " | ");
            strcatFunction(row, doctorReference.getSpecialization());
            strcatFunction(row, " | PKR ");
            strcatFunction(row, feeString);
            strcatFunction(row, "\n\n");
            strcatFunction(displayBuffer, row);
        }
        strcatFunction(displayBuffer, "\nEnter Doctor ID to remove:");
    }

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return && customStrLen(doctorIDStore) > 0) {
        int doctorID = 0;
        for (int i = 0; doctorIDStore[i] != '\0'; i++) {
            doctorID = doctorID * 10 + (doctorIDStore[i] - '0');
        }
        for (int i = 0; i < appointments.arraySize(); i++) {
            Appointment& appointmentReference = appointments.getAll()[i];
            //validate doctor whose appointment and then whether it is still pending or phir agar pending
            //we cant remove
            if (appointmentReference.getDoctorID() == doctorID && stringEqual(appointmentReference.getStatus(), "pending")) {
                StrCpyFunction(statusMessage, "Cannot remove doctor with pending appointments.");
                doctorIDStore[0] = '\0';
                inputString[0] = '\0';
                return;
            }
        }

        FileHandler::deleteDoctor(doctorID);
        reloadAllData();
        StrCpyFunction(statusMessage, "Doctor removed.");
        currentScreen = Screen::ADMIN_MENU;
        doctorIDStore[0] = '\0';
        inputStep = 0;
        inputString[0] = '\0';
        displayBuffer[0] = '\0';
    }
}

void SFMLApp::handleDischargePatient(sf::Event& event) {
    static char patientIDStore[20] = "";

    
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        currentScreen = Screen::ADMIN_MENU;
        patientIDStore[0] = '\0';
        inputStep = 0;
        inputString[0] = '\0';
        statusMessage[0] = '\0';
        displayBuffer[0] = '\0';
        return;
    }
    if (event.type == sf::Event::TextEntered) {
        if (event.text.unicode == 8 && customStrLen(patientIDStore) > 0) {
            patientIDStore[customStrLen(patientIDStore) - 1] = '\0';
        }
        else if (event.text.unicode >= '0' && event.text.unicode <= '9') {
            int len = customStrLen(patientIDStore);
            if (len < 19) {
                patientIDStore[len] = (char)event.text.unicode;
                patientIDStore[len + 1] = '\0';
            }
        }
        StrCpyFunction(inputString, patientIDStore);
    }

    if (customStrLen(displayBuffer) == 0) {
        StrCpyFunction(displayBuffer, "Enter Patient ID to discharge:");
    }

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return && customStrLen(patientIDStore) > 0) {
        int patientID = 0;
        for (int i = 0; patientIDStore[i] != '\0'; i++) {
            patientID = patientID * 10 + (patientIDStore[i] - '0');
        }
        Patient* patient = patients.findID(patientID);
        //checking paihlai kai does patient even exist
        if (!patient) {
            StrCpyFunction(statusMessage, "Patient not found.");
            patientIDStore[0] = '\0';
            inputString[0] = '\0';
            return;
        }//agar it exist phir kia patient ka koi unpaid bill hai
        for (int i = 0; i < bills.arraySize(); i++) {
            Bill& bill = bills.getAll()[i];
            if (bill.getPatientID() == patientID && stringEqual(bill.getStatus(), "unpaid")) {
                StrCpyFunction(statusMessage, "Cannot discharge patient with unpaid bills.");
                patientIDStore[0] = '\0';
                inputString[0] = '\0';
                return;
            }
        }
        //check if patient has paid and etc --> does patient have any appointments
        for (int i = 0; i < appointments.arraySize(); i++) {
            Appointment& appointmerReference = appointments.getAll()[i];
            if (appointmerReference.getPatientID() == patientID && stringEqual(appointmerReference.getStatus(), "pending")) {
                StrCpyFunction(statusMessage, "Cannot discharge patient with pending appointments.");
                patientIDStore[0] = '\0';
                inputString[0] = '\0';
                return;
            }
        }

        FileHandler::dischargePatient(*patient);
        reloadAllData();
        StrCpyFunction(statusMessage, "Patient discharged and archived successfully.");
        currentScreen = Screen::ADMIN_MENU;
        patientIDStore[0] = '\0';
        inputStep = 0;
        inputString[0] = '\0';
        displayBuffer[0] = '\0';
    }
}
//FINAl FUNCTION
void SFMLApp::handleDailyReport(sf::Event& event) {
    if (event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::B)) {
        currentScreen = Screen::ADMIN_MENU;
        displayBuffer[0] = '\0';
        return;

    }
    if (customStrLen(displayBuffer) == 0) {
        char today[11];
        getTodayDate(today);
        int totalAppointments = 0, pending = 0, completed = 0, noShow = 0, cancelled = 0;
        double revenueToday = 0.0;
        //take appointment storage--> if date same as today --> increase total appointment
        //do same for the 3 states of appointments
        for (int i = 0; i < appointments.arraySize(); i++) {
            Appointment& appointmentReference = appointments.getAll()[i];
            if (stringEqual(appointmentReference.getDate(), today)) {
                totalAppointments++;
                if (stringEqual(appointmentReference.getStatus(), "pending")) {
                    pending++; 
                }
                else if (stringEqual(appointmentReference.getStatus(), "completed")) {
                    completed++;
                }
                else if (stringEqual(appointmentReference.getStatus(), "no show")) {
                    noShow++;
                }
                else if (stringEqual(appointmentReference.getStatus(), "cancelled")) {
                    cancelled++;
                }
            }
        }
        for (int i = 0; i < bills.arraySize(); i++) {
            Bill& bill = bills.getAll()[i];
            if (stringEqual(bill.getDate(), today) && stringEqual(bill.getStatus(), "paid")) {
                revenueToday += bill.getAmount();
            }
        }

        char totalAppointmentString[20];
        char pendingString[20];
        char completetedString[20];
        char noShowString[20];
        char cancelledString[20];
        char revenueString[50];
        intToStrFunction(totalAppointments, totalAppointmentString, 20);
        intToStrFunction(pending, pendingString, 20);
        intToStrFunction(completed, completetedString, 20);
        intToStrFunction(noShow, noShowString, 20);
        intToStrFunction(cancelled, cancelledString, 20);
        customDoubleToStr(revenueToday, revenueString, 50);

        StrCpyFunction(displayBuffer, "Daily Report - ");
        strcatFunction(displayBuffer, today);
        strcatFunction(displayBuffer, "\n================================\n");
        strcatFunction(displayBuffer, "Total appointments today: ");
        strcatFunction(displayBuffer, totalAppointmentString);
        strcatFunction(displayBuffer, "\n  Pending: ");
        strcatFunction(displayBuffer, pendingString);
        strcatFunction(displayBuffer, "  Completed: ");
        strcatFunction(displayBuffer, completetedString);
        strcatFunction(displayBuffer, "  No-show: ");
        strcatFunction(displayBuffer, noShowString);
        strcatFunction(displayBuffer, "  Cancelled: ");
        strcatFunction(displayBuffer, cancelledString);
        strcatFunction(displayBuffer, "\nRevenue collected today: PKR ");
        strcatFunction(displayBuffer, revenueString);
        strcatFunction(displayBuffer, "\n\nPatients with outstanding unpaid bills:\n");
        
        //owed mai basically jo jo patient kai unpaid woh daal dena 
        bool anyUnpaid = false;
        for (int i = 0; i < patients.arraySize(); i++) {
            Patient& patientReference = patients.getAll()[i];
            double owed = 0.0;
            for (int j = 0; j < bills.arraySize(); j++) {
                Bill& bill = bills.getAll()[j];
                if (bill.getPatientID() == patientReference.getPatientID() && stringEqual(bill.getStatus(), "unpaid")) {
                    owed += bill.getAmount();
                }
            }
            if (owed > 0) {
                char row[200];
                char owedStr[50];
                customDoubleToStr(owed, owedStr, 50);
                StrCpyFunction(row, patientReference.getName());
                strcatFunction(row, " | PKR ");
                strcatFunction(row, owedStr);
                strcatFunction(row, "\n");
                strcatFunction(displayBuffer, row);
                anyUnpaid = true;
            }
        }
        if (!anyUnpaid) {
            strcatFunction(displayBuffer, "None\n");
        }

        strcatFunction(displayBuffer, "\nDoctor-wise summary today:\nDoctor | Completed | Pending | No-show\n");
        for (int i = 0; i < doctors.arraySize(); i++) {
            Doctor& doctorReference = doctors.getAll()[i];
            int doctorCompleted = 0, doctorPending = 0, doctorNoShow = 0;
            for (int j = 0; j < appointments.arraySize(); j++) {
                Appointment& ap = appointments.getAll()[j];
                if (ap.getDoctorID() == doctorReference.getDoctorID() && stringEqual(ap.getDate(), today)) {
                    if (stringEqual(ap.getStatus(), "completed")) {
                        doctorCompleted++;
                    }
                    else if (stringEqual(ap.getStatus(), "pending")) { 
                        doctorPending++; 
                    }
                    else if (stringEqual(ap.getStatus(), "no show")) {
                        doctorNoShow++; 
                    }
                }
            }
            char row[200];
            char doctorCompletedString[10], doctorPendingString[10], doctorNoShowString[10];
            intToStrFunction(doctorCompleted, doctorCompletedString, 10);
            intToStrFunction(doctorPending, doctorPendingString, 10);
            intToStrFunction(doctorNoShow, doctorNoShowString, 10);
            StrCpyFunction(row, doctorReference.getName());
            strcatFunction(row, " | ");
            strcatFunction(row, doctorCompletedString);
            strcatFunction(row, " | ");
            strcatFunction(row, doctorPendingString);
            strcatFunction(row, " | ");
            strcatFunction(row, doctorNoShowString);
            strcatFunction(row, "\n");
            strcatFunction(displayBuffer, row);
        }
    }
}
//THE ENDDDDD