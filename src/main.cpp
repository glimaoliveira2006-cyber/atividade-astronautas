#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Astronauta {
private:
    string cpf;
    string nome;
    int idade;
    bool vivo;
    bool disponivel;
    vector<int> voos;

public:
    Astronauta(string cpf, string nome, int idade) {
        this->cpf = cpf;
        this->nome = nome;
        this->idade = idade;
        vivo = true;
        disponivel = true;
    }

    string getCpf() {
        return cpf;
    }

    string getNome() {
        return nome;
    }

    int getIdade() {
        return idade;
    }

    bool estaVivo() {
        return vivo;
    }

    bool estaDisponivel() {
        return disponivel;
    }

    void embarcar() {
        disponivel = false;
    }

    void desembarcar() {
        if (vivo) {
            disponivel = true;
        }
    }

    void morrer() {
        vivo = false;
        disponivel = false;
    }

    void registrarVoo(int codigo) {
        voos.push_back(codigo);
    }

    int getQuantidadeVoos() {
        return voos.size();
    }

    int getVoo(int posicao) {
        return voos[posicao];
    }
};


class Voo {
private:
    int codigo;
    string estado;
    vector<string> cpfs;

public:
    Voo(int codigo) {
        this->codigo = codigo;
        estado = "planejado";
    }

    int getCodigo() {
        return codigo;
    }

    string getEstado() {
        return estado;
    }

    int getQuantidadeAstronautas() {
        return cpfs.size();
    }

    string getCpf(int posicao) {
        return cpfs[posicao];
    }

    bool temAstronauta(string cpf) {
        for (int i = 0; i < cpfs.size(); i++) {
            if (cpfs[i] == cpf) {
                return true;
            }
        }

        return false;
    }

    void adicionarAstronauta(string cpf) {
        cpfs.push_back(cpf);
    }

    bool removerAstronauta(string cpf) {
        for (int i = 0; i < cpfs.size(); i++) {
            if (cpfs[i] == cpf) {
                cpfs.erase(cpfs.begin() + i);
                return true;
            }
        }

        return false;
    }

    void lancar() {
        estado = "em curso";
    }

    void explodir() {
        estado = "finalizado com explosao";
    }

    void finalizar() {
        estado = "finalizado com sucesso";
    }
};


class Agencia {
private:
    vector<Astronauta> astronautas;
    vector<Voo> voos;

    int buscarAstronauta(string cpf) {
        for (int i = 0; i < astronautas.size(); i++) {
            if (astronautas[i].getCpf() == cpf) {
                return i;
            }
        }

        return -1;
    }

    int buscarVoo(int codigo) {
        for (int i = 0; i < voos.size(); i++) {
            if (voos[i].getCodigo() == codigo) {
                return i;
            }
        }

        return -1;
    }

    int buscarVooPlanejado(int codigo) {
        int pos = buscarVoo(codigo);

        if (pos == -1) {
            cout << "ERRO: voo " << codigo << " nao cadastrado" << endl;
            return -1;
        }

        if (voos[pos].getEstado() != "planejado") {
            cout << "ERRO: voo " << codigo << " nao esta planejado" << endl;
            return -1;
        }

        return pos;
    }

public:
    void cadastrarAstronauta(string cpf, string nome, int idade) {
        if (buscarAstronauta(cpf) != -1) {
            cout << "ERRO: astronauta com CPF " << cpf << " ja cadastrado" << endl;
            return;
        }

        Astronauta astronauta(cpf, nome, idade);
        astronautas.push_back(astronauta);

        cout << "OK: astronauta " << cpf << " cadastrado" << endl;
    }

    void cadastrarVoo(int codigo) {
        if (buscarVoo(codigo) != -1) {
            cout << "ERRO: voo " << codigo << " ja cadastrado" << endl;
            return;
        }

        Voo voo(codigo);
        voos.push_back(voo);

        cout << "OK: voo " << codigo << " cadastrado" << endl;
    }

    void adicionarAstronauta(string cpf, int codigo) {
        int posAstronauta = buscarAstronauta(cpf);

        if (posAstronauta == -1) {
            cout << "ERRO: astronauta " << cpf << " nao cadastrado" << endl;
            return;
        }

        int posVoo = buscarVooPlanejado(codigo);

        if (posVoo == -1) {
            return;
        }

        if (!astronautas[posAstronauta].estaVivo()) {
            cout << "ERRO: astronauta " << cpf << " esta morto" << endl;
            return;
        }

        if (voos[posVoo].temAstronauta(cpf)) {
            cout << "ERRO: astronauta " << cpf << " ja esta no voo " << codigo << endl;
            return;
        }

        voos[posVoo].adicionarAstronauta(cpf);

        cout << "OK: astronauta " << cpf << " adicionado ao voo " << codigo << endl;
    }

    void removerAstronauta(string cpf, int codigo) {
        int posAstronauta = buscarAstronauta(cpf);

        if (posAstronauta == -1) {
            cout << "ERRO: astronauta " << cpf << " nao cadastrado" << endl;
            return;
        }

        int posVoo = buscarVooPlanejado(codigo);

        if (posVoo == -1) {
            return;
        }

        if (!voos[posVoo].temAstronauta(cpf)) {
            cout << "ERRO: astronauta " << cpf << " nao esta no voo " << codigo << endl;
            return;
        }

        voos[posVoo].removerAstronauta(cpf);

        cout << "OK: astronauta " << cpf << " removido do voo " << codigo << endl;
    }

    void lancarVoo(int codigo) {
        int posVoo = buscarVooPlanejado(codigo);

        if (posVoo == -1) {
            return;
        }

        if (voos[posVoo].getQuantidadeAstronautas() == 0) {
            cout << "ERRO: voo " << codigo << " nao possui astronautas" << endl;
            return;
        }

        for (int i = 0; i < voos[posVoo].getQuantidadeAstronautas(); i++) {
            string cpf = voos[posVoo].getCpf(i);
            int posAstronauta = buscarAstronauta(cpf);

            if (!astronautas[posAstronauta].estaVivo()) {
                cout << "ERRO: astronauta " << cpf << " esta morto" << endl;
                return;
            }

            if (!astronautas[posAstronauta].estaDisponivel()) {
                cout << "ERRO: astronauta " << cpf << " esta indisponivel" << endl;
                return;
            }
        }

        for (int i = 0; i < voos[posVoo].getQuantidadeAstronautas(); i++) {
            string cpf = voos[posVoo].getCpf(i);
            int posAstronauta = buscarAstronauta(cpf);

            astronautas[posAstronauta].embarcar();
            astronautas[posAstronauta].registrarVoo(codigo);
        }

        voos[posVoo].lancar();

        cout << "OK: voo " << codigo << " lancado" << endl;
    }

    void explodirVoo(int codigo) {
        int posVoo = buscarVoo(codigo);

        if (posVoo == -1) {
            cout << "ERRO: voo " << codigo << " nao cadastrado" << endl;
            return;
        }

        if (voos[posVoo].getEstado() != "em curso") {
            cout << "ERRO: voo " << codigo << " nao esta em curso" << endl;
            return;
        }

        for (int i = 0; i < voos[posVoo].getQuantidadeAstronautas(); i++) {
            string cpf = voos[posVoo].getCpf(i);
            int posAstronauta = buscarAstronauta(cpf);

            astronautas[posAstronauta].morrer();
        }

        voos[posVoo].explodir();

        cout << "OK: voo " << codigo << " explodiu" << endl;
    }

    void finalizarVoo(int codigo) {
        int posVoo = buscarVoo(codigo);

        if (posVoo == -1) {
            cout << "ERRO: voo " << codigo << " nao cadastrado" << endl;
            return;
        }

        if (voos[posVoo].getEstado() != "em curso") {
            cout << "ERRO: voo " << codigo << " nao esta em curso" << endl;
            return;
        }

        for (int i = 0; i < voos[posVoo].getQuantidadeAstronautas(); i++) {
            string cpf = voos[posVoo].getCpf(i);
            int posAstronauta = buscarAstronauta(cpf);

            astronautas[posAstronauta].desembarcar();
        }

        voos[posVoo].finalizar();

        cout << "OK: voo " << codigo << " finalizado com sucesso" << endl;
    }

    void listarVoos() {
        cout << "LISTA DE VOOS" << endl;

        string estados[4] = {
            "planejado",
            "em curso",
            "finalizado com sucesso",
            "finalizado com explosao"
        };

        for (int e = 0; e < 4; e++) {
            cout << "== " << estados[e] << " ==" << endl;

            bool encontrou = false;

            for (int i = 0; i < voos.size(); i++) {
                if (voos[i].getEstado() == estados[e]) {
                    encontrou = true;

                    cout << "Voo " << voos[i].getCodigo() << ": ";

                    if (voos[i].getQuantidadeAstronautas() == 0) {
                        cout << "sem astronautas" << endl;
                    } else {
                        for (int j = 0; j < voos[i].getQuantidadeAstronautas(); j++) {
                            string cpf = voos[i].getCpf(j);
                            int posAstronauta = buscarAstronauta(cpf);

                            if (j > 0) {
                                cout << ", ";
                            }

                            cout << astronautas[posAstronauta].getCpf()
                                 << " "
                                 << astronautas[posAstronauta].getNome();
                        }

                        cout << endl;
                    }
                }
            }

            if (!encontrou) {
                cout << "(nenhum)" << endl;
            }
        }
    }

    void listarMortos() {
        cout << "ASTRONAUTAS MORTOS" << endl;

        bool encontrou = false;

        for (int i = 0; i < astronautas.size(); i++) {
            if (!astronautas[i].estaVivo()) {
                encontrou = true;

                cout << astronautas[i].getCpf()
                     << " "
                     << astronautas[i].getNome()
                     << " - voos:";

                bool participou = false;

                for (int j = 0; j < voos.size(); j++) {
                    if (voos[j].getEstado() != "planejado" &&
                        voos[j].temAstronauta(astronautas[i].getCpf())) {

                        cout << " " << voos[j].getCodigo();
                        participou = true;
                    }
                }

                if (!participou) {
                    cout << " nenhum";
                }

                cout << endl;
            }
        }

        if (!encontrou) {
            cout << "(nenhum)" << endl;
        }
    }

    void listarAstronautas() {
        cout << "LISTA DE ASTRONAUTAS" << endl;

        cout << "== disponiveis ==" << endl;

        bool encontrou = false;

        for (int i = 0; i < astronautas.size(); i++) {
            if (!astronautas[i].estaVivo()) {
                continue;
            }

            bool emVoo = false;

            for (int j = 0; j < voos.size(); j++) {
                if (voos[j].getEstado() == "em curso" &&
                    voos[j].temAstronauta(astronautas[i].getCpf())) {

                    emVoo = true;
                    break;
                }
            }

            if (!emVoo) {
                encontrou = true;

                cout << astronautas[i].getCpf()
                     << " "
                     << astronautas[i].getNome()
                     << " ("
                     << astronautas[i].getIdade()
                     << " anos)"
                     << endl;
            }
        }

        if (!encontrou) {
            cout << "(nenhum)" << endl;
        }

        cout << "== em voo ==" << endl;

        encontrou = false;

        for (int i = 0; i < astronautas.size(); i++) {
            if (!astronautas[i].estaVivo()) {
                continue;
            }

            int codigoVoo = -1;

            for (int j = 0; j < voos.size(); j++) {
                if (voos[j].getEstado() == "em curso" &&
                    voos[j].temAstronauta(astronautas[i].getCpf())) {

                    codigoVoo = voos[j].getCodigo();
                    break;
                }
            }

            if (codigoVoo != -1) {
                encontrou = true;

                cout << astronautas[i].getCpf()
                     << " "
                     << astronautas[i].getNome()
                     << " ("
                     << astronautas[i].getIdade()
                     << " anos)"
                     << " - voo "
                     << codigoVoo
                     << endl;
            }
        }

        if (!encontrou) {
            cout << "(nenhum)" << endl;
        }

        cout << "== mortos ==" << endl;

        encontrou = false;

        for (int i = 0; i < astronautas.size(); i++) {
            if (!astronautas[i].estaVivo()) {
                encontrou = true;

                cout << astronautas[i].getCpf()
                     << " "
                     << astronautas[i].getNome()
                     << " ("
                     << astronautas[i].getIdade()
                     << " anos)"
                     << endl;
            }
        }

        if (!encontrou) {
            cout << "(nenhum)" << endl;
        }
    }

    void listarHistorico(string cpf) {
        int posAstronauta = buscarAstronauta(cpf);

        if (posAstronauta == -1) {
            cout << "ERRO: astronauta " << cpf << " nao cadastrado" << endl;
            return;
        }

        cout << "HISTORICO DE "
             << astronautas[posAstronauta].getCpf()
             << " "
             << astronautas[posAstronauta].getNome()
             << endl;

        if (astronautas[posAstronauta].getQuantidadeVoos() == 0) {
            cout << "(nenhum voo)" << endl;
            return;
        }

        for (int i = 0; i < astronautas[posAstronauta].getQuantidadeVoos(); i++) {
            int codigo = astronautas[posAstronauta].getVoo(i);
            int posVoo = buscarVoo(codigo);

            cout << "voo "
                 << codigo
                 << ": "
                 << voos[posVoo].getEstado()
                 << endl;
        }
    }

    void salvar(string nomeArquivo) {
        ofstream arquivo(nomeArquivo);

        if (!arquivo) {
            cout << "ERRO: nao foi possivel salvar em " << nomeArquivo << endl;
            return;
        }

        arquivo << "ASTRONAUTAS " << astronautas.size() << endl;

        for (int i = 0; i < astronautas.size(); i++) {
            arquivo << astronautas[i].getCpf() << endl;
            arquivo << astronautas[i].getNome() << endl;
            arquivo << astronautas[i].getIdade() << endl;
            arquivo << astronautas[i].estaVivo() << " " << astronautas[i].estaDisponivel() << endl;
            arquivo << astronautas[i].getQuantidadeVoos() << endl;

            for (int j = 0; j < astronautas[i].getQuantidadeVoos(); j++) {
                arquivo << astronautas[i].getVoo(j) << endl;
            }
        }

        arquivo << "VOOS " << voos.size() << endl;

        for (int i = 0; i < voos.size(); i++) {
            arquivo << voos[i].getCodigo() << endl;
            arquivo << voos[i].getEstado() << endl;
            arquivo << voos[i].getQuantidadeAstronautas() << endl;

            for (int j = 0; j < voos[i].getQuantidadeAstronautas(); j++) {
                arquivo << voos[i].getCpf(j) << endl;
            }
        }

        arquivo.close();

        cout << "OK: dados salvos em " << nomeArquivo << endl;
    }

    void carregar(string nomeArquivo) {
        ifstream arquivo(nomeArquivo);

        if (!arquivo) {
            cout << "ERRO: nao foi possivel carregar de " << nomeArquivo << endl;
            return;
        }

        string rotulo;
        int quantidade;

        arquivo >> rotulo >> quantidade;

        if (arquivo.fail()) {
            cout << "ERRO: nao foi possivel carregar de " << nomeArquivo << endl;
            return;
        }

        vector<Astronauta> novosAstronautas;

        for (int i = 0; i < quantidade; i++) {
            string cpf, nome;
            int idade, vivo, disponivel, nvoos;

            arquivo >> cpf;
            getline(arquivo >> ws, nome);
            arquivo >> idade;
            arquivo >> vivo >> disponivel;
            arquivo >> nvoos;

            Astronauta astronauta(cpf, nome, idade);

            if (!vivo) {
                astronauta.morrer();
            } else if (!disponivel) {
                astronauta.embarcar();
            }

            for (int j = 0; j < nvoos; j++) {
                int codigo;
                arquivo >> codigo;
                astronauta.registrarVoo(codigo);
            }

            novosAstronautas.push_back(astronauta);
        }

        arquivo >> rotulo >> quantidade;

        if (arquivo.fail()) {
            cout << "ERRO: nao foi possivel carregar de " << nomeArquivo << endl;
            return;
        }

        vector<Voo> novosVoos;

        for (int i = 0; i < quantidade; i++) {
            int codigo, ncpfs;
            string estado;

            arquivo >> codigo;
            getline(arquivo >> ws, estado);
            arquivo >> ncpfs;

            Voo voo(codigo);

            for (int j = 0; j < ncpfs; j++) {
                string cpf;
                arquivo >> cpf;
                voo.adicionarAstronauta(cpf);
            }

            if (estado == "em curso") {
                voo.lancar();
            } else if (estado == "finalizado com sucesso") {
                voo.lancar();
                voo.finalizar();
            } else if (estado == "finalizado com explosao") {
                voo.lancar();
                voo.explodir();
            }

            novosVoos.push_back(voo);
        }

        astronautas = novosAstronautas;
        voos = novosVoos;

        cout << "OK: dados carregados de " << nomeArquivo << endl;
    }
};


int main() {
    Agencia agencia;

    string comando;

    while (cin >> comando) {
        if (comando == "FIM") {
            break;
        } else if (comando == "CADASTRAR_ASTRONAUTA") {
            string cpf, nome;
            int idade;
            cin >> cpf >> idade;
            getline(cin >> ws, nome);
            if (!nome.empty() && nome.back() == '\r') {
                nome.pop_back();
            }
            agencia.cadastrarAstronauta(cpf, nome, idade);

        } else if (comando == "CADASTRAR_VOO") {
            int codigo;
            cin >> codigo;
            agencia.cadastrarVoo(codigo);

        } else if (comando == "ADICIONAR_ASTRONAUTA") {
            string cpf;
            int codigo;
            cin >> cpf >> codigo;
            agencia.adicionarAstronauta(cpf, codigo);

        } else if (comando == "REMOVER_ASTRONAUTA") {
            string cpf;
            int codigo;
            cin >> cpf >> codigo;
            agencia.removerAstronauta(cpf, codigo);

        } else if (comando == "LANCAR_VOO") {
            int codigo;
            cin >> codigo;
            agencia.lancarVoo(codigo);

        } else if (comando == "EXPLODIR_VOO") {
            int codigo;
            cin >> codigo;
            agencia.explodirVoo(codigo);

        } else if (comando == "FINALIZAR_VOO") {
            int codigo;
            cin >> codigo;
            agencia.finalizarVoo(codigo);

        } else if (comando == "LISTAR_VOOS") {
            agencia.listarVoos();

        } else if (comando == "LISTAR_MORTOS") {
            agencia.listarMortos();

        } else if (comando == "LISTAR_ASTRONAUTAS") {
            agencia.listarAstronautas();

        } else if (comando == "HISTORICO") {
            string cpf;
            cin >> cpf;
            agencia.listarHistorico(cpf);

        } else if (comando == "SALVAR") {
            string nomeArquivo;
            cin >> nomeArquivo;
            agencia.salvar(nomeArquivo);

        } else if (comando == "CARREGAR") {
            string nomeArquivo;
            cin >> nomeArquivo;
            agencia.carregar(nomeArquivo);

        } else {
            cout << "ERRO: comando desconhecido " << comando << endl;
        }
    }

    return 0;
}