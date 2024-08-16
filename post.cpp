include <iostream>
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

                                                                                                                                    69,1          Bot


