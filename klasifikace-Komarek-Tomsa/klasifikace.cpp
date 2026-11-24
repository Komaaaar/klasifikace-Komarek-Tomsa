#include <iostream>
#include <iomanip>
#include <array>
#include <string>
#include <algorithm>

const int STUDENTI = 6;
const int PREDMETY = 4;

std::array<std::string, STUDENTI> jmena = {"Adam", "Eva", "Jan", "Lucie", "Marek", "Petra"};
std::array<std::string, PREDMETY> predmety = {"PRG", "MAT", "CJL", "ANJ"};

int znamky[STUDENTI][PREDMETY] = {
    {1, 2, 3, 1},
    {2, 2, 1, 1},
    {3, 4, 2, 3},
    {1, 1, 1, 2},
    {5, 3, 4, 4},
    {2, 3, 2, 2}
};

double prumerStudenta(const int (&z)[STUDENTI][PREDMETY], int student);
double prumerPredmetu(const int (&z)[STUDENTI][PREDMETY], int predmet);

void vypisTabulku(const int (&z)[STUDENTI][PREDMETY]) {
    std::cout << std::setw(11) << "";
    for (size_t j = 0; j < predmety.size(); ++j) {
        std::cout << std::setw(6) << predmety[j];
    }
    std::cout << std::setw(8) << "prumer" << '\n';

    std::cout << std::fixed << std::setprecision(2);
    for (size_t i = 0; i < jmena.size(); ++i) {
        std::cout << std::setw(11) << jmena[i];
        for (size_t j = 0; j < predmety.size(); ++j) {
            std::cout << std::setw(6) << z[i][j];
        }
        std::cout << std::setw(8) << prumerStudenta(z, static_cast<int>(i)) << '\n';
    }

    std::cout << std::setw(11) << "prumer";
    for (size_t j = 0; j < predmety.size(); ++j) {
        std::cout << std::setw(6) << prumerPredmetu(z, static_cast<int>(j));
    }
    std::cout << '\n';
}

int prvniStudentSeZnamkou(const int (&z)[STUDENTI][PREDMETY], int znamka) {
    for (int i = 0; i < STUDENTI; ++i) {
        for (int j = 0; j < PREDMETY; ++j) {
            if (z[i][j] == znamka) {
                return i;
            }
        }
    }
    return -1;
}

double prumerStudenta(const int (&z)[STUDENTI][PREDMETY], int student) {
    int soucet = 0;
    for (int j = 0; j < PREDMETY; ++j) {
        soucet += z[student][j];
    }
    return static_cast<double>(soucet) / PREDMETY;
}

double prumerPredmetu(const int (&z)[STUDENTI][PREDMETY], int predmet) {
    int soucet = 0;
    for (int i = 0; i < STUDENTI; ++i) {
        soucet += z[i][predmet];
    }
    return static_cast<double>(soucet) / STUDENTI;
}

template <typename T>
int indexMinima(const T pole[], int velikost) {
    int idxMin = 0;
    for (int i = 1; i < velikost; ++i) {
        if (pole[i] < pole[idxMin]) {
            idxMin = i;
        }
    }
    return idxMin;
}

template <typename T>
int indexMaxima(const T pole[], int velikost) {
    int idxMax = 0;
    for (int i = 1; i < velikost; ++i) {
        if (pole[i] > pole[idxMax]) {
            idxMax = i;
        }
    }
    return idxMax;
}

int main() {
    vypisTabulku(znamky);

    int idxPetka = prvniStudentSeZnamkou(znamky, 5);
    std::cout << "Prvni s petkou: "
              << (idxPetka != -1 ? jmena[idxPetka] : "nikdo") << '\n';

    int idxSestka = prvniStudentSeZnamkou(znamky, 6);
    if (idxSestka == -1) {
        std::cout << "Znamku 6 nema zadny student.\n";
    }

    double prumeryPredmetu[PREDMETY];
    int poradiPredmetu[PREDMETY] = {0, 1, 2, 3};
    for (int j = 0; j < PREDMETY; ++j) {
        prumeryPredmetu[j] = prumerPredmetu(znamky, j);
    }
    std::sort(poradiPredmetu, poradiPredmetu + PREDMETY, [&prumeryPredmetu](int a, int b) {
        return prumeryPredmetu[a] < prumeryPredmetu[b];
    });
    std::cout << "Predmety od nejlepsiho:\n";
    std::cout << std::fixed << std::setprecision(2);
    for (int j = 0; j < PREDMETY; ++j) {
        int idx = poradiPredmetu[j];
        std::cout << predmety[idx] << " " << prumeryPredmetu[idx] << '\n';
    }

    double prumery[STUDENTI];
    for (int i = 0; i < STUDENTI; ++i) {
        prumery[i] = prumerStudenta(znamky, i);
    }

    int idxNejlepsi = indexMinima(prumery, STUDENTI);
    int idxNejhorsi = indexMaxima(prumery, STUDENTI);
    std::cout << "Nejlepsi: " << jmena[idxNejlepsi] << '\n';
    std::cout << "Nejhorsi: " << jmena[idxNejhorsi] << '\n';

    int poradiTridy[STUDENTI] = {0, 1, 2, 3, 4, 5};
    std::sort(poradiTridy, poradiTridy + STUDENTI, [&prumery](int a, int b) {
        return prumery[a] < prumery[b];
    });
    std::cout << "Poradi tridy:\n";
    std::cout << std::fixed << std::setprecision(2);
    for (int i = 0; i < STUDENTI; ++i) {
        int idx = poradiTridy[i];
        std::cout << (i + 1) << ". " << jmena[idx] << " (" << prumery[idx] << ")\n";
    }

    return 0;
}