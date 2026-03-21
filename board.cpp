#include "board.h"
#include <memory>
#include <iostream>
using namespace std;
Board::Board(int width, int height)// Implementado :D
    :   m_ancho(width);
        m_altura(height); //inicializacion d'atributos (lo dice en la guia d'estil) es como m_ancho = width;
{
    for(int i = 0; i < m_ancho; i++)
    {
        for(int j = 0; j < height; j++)
        {
            m_matriz[i][j] = nullptr; //nullptr es un puntero nulo (mas safe)
        }

    }
}

Board::~Board()
{
    // Implement your code here
}


Candy* Board::getCell(int x, int y) const // Implementado :D
{
    if ((x >= m_ancho) || (x < 0)) || (y >= m_altura) || (y < 0)//mira is x y estan en el tablero
    {
        return nullptr;
    }

    return m_matriz[x][y];
}

void Board::setCell(Candy* candy, int x, int y) // Implementado :D
{
    
    if ((x < m_ancho) && (x >= 0)) && (y < m_altura) && (y >= 0)//mira is x y estan en el tablero
    {
        m_matriz[x][y] = candy;
    }
    
}


int Board::getWidth() const
{
    // Implementado :D
    return m_ancho;
}


int Board::getHeight() const
{
    // Implementado :D
    return m_altura;
}
bool Board::comprobarEnFila(int x, int y, CandyType tipo) const
{
    bool debeExplotar = false;
    bool izquierdaIgual = false;
    bool derechaIgual = false;


    //hacia la izq
    Candy* igualIzq1 = getCell(x - 1, y);

    if (igualIzq1 != nullptr && igualIzq1->getType() == tipo)
    {
        izquierdaIgual = true; //xxOCOxx
        Candy* igualIzq2 = getCell(x - 2, y);

        if(igualIzq2 != nullptr && igualIzq2->getType() == tipo)
        {
            debeExplotar = true;
        }
    }

    //hacia la derecha
    Candy* igualDer1 = getCell(x + 1, y);
    if (igualDer1 != nullptr && igualDer1->getType() == tipo)
    {
        derechaIgual = true; //xxOCOxx
        Candy* igualDer2 = getCell(x + 2, y);

        if (igualDer2 != nullptr && igualDer2->getType() == tipo)
        {
            debeExplotar = true;
        }
    }

    //central i lados
    if (izquierdaIgual && derechaIgual) {debeExplotar = true;}
    return debeExplotar;
}
bool Board::comprobarEnColumna(int x, int y, CandyType tipo) const
{
    bool debeExplotar = false;
    bool arribaIgual = false;
    bool abajoIgual = false;

    //hacia arriba 
    Candy* igualArriba1 = getCell(x, y - 1);
    if (igualArriba1 != nullptr && igualArriba1->getType() == tipo)
    {
        arribaIgual = true; 
        Candy* igualArriba2 = getCell(x, y - 2);

        if (igualArriba2 != nullptr && igualArriba2->getType() == tipo)
        {
            debeExplotar = true;
        }
    }

    //hacia abajo 
    Candy* igualAbajo1 = getCell(x, y + 1);
    if (igualAbajo1 != nullptr && igualAbajo1->getType() == tipo)
    {
        abajoIgual = true; 
        Candy* igualAbajo2 = getCell(x, y + 2);

        if (igualAbajo2 != nullptr && igualAbajo2->getType() == tipo)
        {
            debeExplotar = true;
        }
    }

    //central Up down cerca
    if (arribaIgual && abajoIgual) 
    {
        debeExplotar = true;
    }
    
    return debeExplotar;
}
bool Board::comprobarDiagonales(int x, int y, CandyType tipo) const
{
    bool debeExplotar = false;
    bool arribaIzqIgual = false;
    bool abajoDerIgual = false;

    //hacia arriba IZQ
    Candy* arribaIzquierda1 = getCell(x - 1, y - 1);
    if (arribaIzquierda1 != nullptr && arribaIzquierda1->getType() == tipo)
    {
        arribaIzqIgual = true; 
        Candy* arribaIzquierda2 = getCell(x - 2, y - 2);

        if (arribaIzquierda2 != nullptr && arribaIzquierda2->getType() == tipo)
        {
            debeExplotar = true;
        }
    }
    //hacia abajo Derecha
    Candy* abajoDerecha1 = getCell(x + 1, y + 1);
    if (abajoDerecha1 != nullptr && abajoDerecha1->getType() == tipo)
    {
        abajoDerIgual = true; 
        Candy* abajoDerecha2 = getCell(x + 2, y + 2);

        if (abajoDerecha2 != nullptr && abajoDerecha2->getType() == tipo)
        {
            debeExplotar = true;
        }
    }

    // Caso central UpL DownR
    if (arribaIzqIgual && abajoDerIgual) 
    {
        debeExplotar = true;
    }


    //-----------LA OTRA DIAGONAL -----------
    bool arribaDerIgual = false;
    bool abajoIzqIgual = false;

    // ArribaDERECHA
    Candy* arribaDerecha1 = getCell(x + 1, y - 1);
    if (arribaDerecha1 != nullptr && arribaDerecha1->getType() == tipo)
    {
        arribaDerIgual = true; 
        Candy* arribaDerecha2 = getCell(x + 2, y - 2);

        if (arribaDerecha2 != nullptr && arribaDerecha2->getType() == tipo)
        {
            debeExplotar = true;
        }
    }

    //AbajoIZQUIERDA
    Candy* abajoIzquierda1 = getCell(x - 1, y + 1);
    if (abajoIzquierda1 != nullptr && abajoIzquierda1->getType() == tipo)
    {
        abajoIzqIgual = true; 
        Candy* abajoIzquierda2 = getCell(x - 2, y + 2);

        if (abajoIzquierda2 != nullptr && abajoIzquierda2->getType() == tipo)
        {
            debeExplotar = true;
        }
    }

    // Caso central
    if (arribaDerIgual && abajoIzqIgual) 
    {
        debeExplotar = true;
    }

    return debeExplotar;
}
bool Board::shouldExplode(int x, int y) const
{
    
    //pillamos el caramelo y el tipo (antes estaba en cada cmoprobacion)
    Candy* carameloCentral = getCell(x, y);
    if (carameloCentral == nullptr) 
    {
        return false;
    }

    CandyType tipo = carameloCentral->getType();
    if (comprobarEnFila(x, y, tipo)){return true;} 
    if (comprobarEnColumna(x, y, tipo)){return true;} 
    if (comprobarDiagonales(x, y, tipo)) {return true;} 
    
    return false;
}

std::vector<Candy*> Board::explodeAndDrop()
{
    // Implement your code here
    return {};
}

bool Board::dump(const std::string& output_path) const
{
    #include <fstream>
#include <string>

bool Board::dump(const std::string& output_path) const
{
    ofstream archivo;
    archivo.open(output_path);

    if (!archivo.is_open())
    {
        return false;
    }

    for (int y = 0; y < m_height; y++)
    {
        for (int x = 0; x < m_width; x++)
        {
            Candy* caramelo = getCell(x, y);

            if (caramelo == nullptr)
            {
                archivo << ".";
            }
            else
            {
                switch (caramelo.getType()){
                    case CandyType::TYPE_RED:
                        archivo << 'R';
                        break;
                    case CandyType::TYPE_GREEN:
                        archivo << 'G';
                        break;
                    case CandyType::TYPE_YELLOW:
                        archivo << 'Y';
                        break;
                    case CandyType::TYPE_BLUE:
                        archivo << 'B';
                        break;
                    case CandyType::TYPE_PURPLE:
                        archivo << 'P';
                        break;
                    case CandyType::TYPE_ORANGE:
                        archivo << 'O';
                        break;
                }

                archivo << ' ';
            }
        }
        
        archivo << endl;
    }

    archivo.close();
    
    return true;
}
}

bool Board::load(const std::string& input_path)
{
    #include <fstream>
#include <string>

bool Board::dump(const std::string& output_path) const
{
    ifstream archivo;
    archivo.open(output_path);

    if (!archivo.is_open())
    {
        return false;
    }

    for (int y = 0; y < m_height; y++)
    {
        for (int x = 0; x < m_width; x++)
        {
            Candy* caramelo = getCell(x, y);

            if (caramelo == '.')
            {
                m_matriz[x][y] = nullptr;
            }
            else
            {
                switch (caramelo.getType()){
                    case 'R':
                        Candy candy = Candy(TYPE_RED);
                        m_matriz[i][j] = &candy;
                        break;
                    case 'G'
                        Candy candy = Candy(TYPE_GREEN);
                        m_matriz[i][j] = &candy;
                        break;
                    case 'Y':
                        Candy candy = Candy(TYPE_YELLOW);
                        m_matriz[i][j] = &candy;
                        break;
                    case 'B':
                        Candy candy = Candy(TYPE_BLUE);
                        m_matriz[i][j] = &candy;
                        break;
                    case 'P':
                        Candy candy = Candy(TYPE_PURPLE);
                        m_matriz[i][j] = &candy;
                        break;
                    case 'O':
                        Candy candy = Candy(TYPE_ORANGE);
                        m_matriz[i][j] = &candy;
                        break;
                }
            }
        }
        
        archivo << endl;
    }

    archivo.close();
    
    return true;
}
}
