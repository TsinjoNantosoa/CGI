#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

bool validateUser(const string& login, const string& password) {
    ifstream file("data1.txt");
    string line;
    string storedLogin, storedPassword;

    while (getline(file, line)) {
        // Read username
        storedLogin = line;
        // Read password
        if (getline(file, line)) {
            storedPassword = line;
        }

        // Compare with input
        if (login == storedLogin && password == storedPassword) {
            return true;
        }
    }
    return false;
}

int main() {
    // Récupérer les données via la méthode GET
    char *query_string = getenv("QUERY_STRING");

    string login, password;

    if (query_string != nullptr) {
        string query = query_string;
        size_t pos = 0;
        while ((pos = query.find('&')) != string::npos) {
            string token = query.substr(0, pos);
            size_t eq = token.find('=');
            if (eq != string::npos) {
                string key = token.substr(0, eq);
                string value = token.substr(eq + 1);
                if (key == "login") login = value;
                else if (key == "password") password = value;
            }
            query.erase(0, pos + 1);
        }
    }

    // Vérifier les informations d'identification
    bool isValid = validateUser(login, password);

    // Générer la réponse HTML
    cout << "Content-type: text/html\n\n";
    cout << "<!DOCTYPE html>\n";
    cout << "<html lang=\"fr\">\n";
    cout << "<head>\n";
    cout << "    <meta charset=\"UTF-8\">\n";
    cout << "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n";
    cout << "    <title>" << (isValid ? "Connexion réussie" : "Échec de la connexion") << "</title>\n";
    cout << "</head>\n";
    cout << "<body>\n";
    cout << "<div class=\"form-container\">\n";
    if (isValid) {
        cout << "    <h2>Connexion réussie</h2>\n";
        cout << "    <p>Bienvenue, " << login << "!</p>\n";
    } else {
        cout << "    <h2>Échec de la connexion</h2>\n";
        cout << "    <p>Nom d'utilisateur ou mot de passe incorrect.</p>\n";
        cout << "    <a href=\"/cgi-bin/post.htm\">Réessayer</a>\n";
    }
    cout << "</div>\n";
    cout << "</body>\n";
    cout << "</html>\n";

    return 0;
}

root@tsinjo-CF-AX2L-50MF:/home/tsinjo# mv post.cpp /var/www/site/site3
root@tsinjo-CF-AX2L-50MF:/home/tsinjo# cd /var/www/site/site3
root@tsinjo-CF-AX2L-50MF:/var/www/site/site3# ls
data1.txt  data.txt  inscription.html  login.html  post.cpp  post.html
root@tsinjo-CF-AX2L-50MF:/var/www/site/site3# g++ -o post.cgi post.cpp
root@tsinjo-CF-AX2L-50MF:/var/www/site/site3# ls
data1.txt  data.txt  inscription.html  login.html  post.cgi  post.cpp  post.html
root@tsinjo-CF-AX2L-50MF:/var/www/site/site3# mv post.cgi /usr/lib/cgi-bin/
root@tsinjo-CF-AX2L-50MF:/var/www/site/site3# systemctl reload apache2
root@tsinjo-CF-AX2L-50MF:/var/www/site/site3# a2ensite site3
Site site3 already enabled
root@tsinjo-CF-AX2L-50MF:/var/www/site/site3# vim post.cpp 
root@tsinjo-CF-AX2L-50MF:/var/www/site/site3# vim post.html
root@tsinjo-CF-AX2L-50MF:/var/www/site/site3# ls
data1.txt  data.txt  inscription.html  login.html  post.cpp  post.html
root@tsinjo-CF-AX2L-50MF:/var/www/site/site3# vim login.html 
root@tsinjo-CF-AX2L-50MF:/var/www/site/site3# cd /
root@tsinjo-CF-AX2L-50MF:/# cd home/tsinjo/
root@tsinjo-CF-AX2L-50MF:/home/tsinjo# cat login.cpp 
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
using namespace std;

// Fonction pour comparer les données avec le fichier data.txt
bool verifierConnexion(const char* name, const char* login, const char* password) {
    ifstream file("data.txt");
    string fileName, fileLogin, filePassword;

    while (file >> fileName >> fileLogin >> filePassword) {
        if (fileName == name && fileLogin == login && filePassword == password) {
            return true;  // Connexion réussie
        }
    }
    return false;  // Connexion échouée
}

int main() {
    // Récupérer les données via la méthode GET
    char* query_string = getenv("QUERY_STRING");

    // Variables pour stocker les données GET
    char name[100] = {0}, login[100] = {0}, password[100] = {0};

    // Analyse des données GET
    if (query_string != nullptr) {
        char* name_pos = strstr(query_string, "name=");
        char* login_pos = strstr(query_string, "login=");
        char* password_pos = strstr(query_string, "password=");

        if (name_pos != nullptr) {
            name_pos += 5;
            char* end = strchr(name_pos, '&');
            if (end != nullptr) *end = '\0';
            strncpy(name, name_pos, sizeof(name) - 1);
        }

        if (login_pos != nullptr) {
            login_pos += 6;
            char* end = strchr(login_pos, '&');
            if (end != nullptr) *end = '\0';
            strncpy(login, login_pos, sizeof(login) - 1);
        }

        if (password_pos != nullptr) {
            password_pos += 9;
            char* end = strchr(password_pos, '&');
            if (end != nullptr) *end = '\0';
            strncpy(password, password_pos, sizeof(password) - 1);
        }
    }

    // Générer la réponse HTML
    cout << "Content-type: text/html\n\n";
    cout << "<!DOCTYPE html>\n";
    cout << "<html lang=\"fr\">\n";
    cout << "<head>\n";
    cout << "    <meta charset=\"UTF-8\">\n";
    cout << "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n";
    cout << "    <title>Confirmation de connexion</title>\n";
    cout << "</head>\n";
    cout << "<body>\n";
    cout << "<div class=\"form-container\">\n";

    if (verifierConnexion(name, login, password)) {
        cout << "    <h2>Connexion réussie</h2>\n";
        cout << "    <p>Nom: " << name << "</p>\n";
        cout << "    <p>Login: " << login << "</p>\n";
    } else {
        cout << "    <h2>Connexion échouée</h2>\n";
        cout << "    <p>Veuillez vérifier vos informations.</p>\n";
        cout << "    <button onclick=\"history.back()\">Retour</button>\n";
    }

    cout << "</div>\n";
    cout << "</body>\n";
    cout << "</html>\n";

    return 0;
}

