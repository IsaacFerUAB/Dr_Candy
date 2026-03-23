#include "board.h"
#include <memory>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
Board::Board(int width, int height)
{
    m_ancho = width;
    m_altura = height;

    for(int i = 0; i < DEFAULT_BOARD_WIDTH; i++)
    {
        for(int j = 0; j < DEFAULT_BOARD_HEIGHT; j++)
        {
            m_matriz[i][j] = nullptr; //nullptr es un puntero nulo (mas safe)
        }
    }
}

Board::~Board()
{
    
    // Implement
}


Candy* Board::getCell(int x, int y) const // Implementado :D
{
    if ((x >= m_ancho) || (x < 0) || (y >= m_altura) || (y < 0))//mira is x y estan en el tablero
    {
        return nullptr;
    }
    return m_matriz[x][y];
}

void Board::setCell(Candy* candy, int x, int y) // Implementado :D
{
    
    if ((x < m_ancho) && (x >= 0) && (y < m_altura) && (y >= 0))//mira is x y estan en el tablero
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
    if (comprobarEnFila(x, y, tipo))
        {
            return true;
        }
    if (comprobarEnColumna(x, y, tipo))
        {
            return true;
        } 
    if (comprobarDiagonales(x, y, tipo)) 
        {
            return true;
        } 
    
    return false;
}

vector<Candy*> Board::explodeAndDrop()
{
    // Implement your code here
    vector<Candy*> caramelosExplotados;
    bool auxExplosion[DEFAULT_BOARD_WIDTH][DEFAULT_BOARD_HEIGHT];
    bool sinExplosiones;
    bool sinCaidas;
    do {
        sinExplosiones = true;
        sinCaidas = true;
        //bucle que recorre todo el tablero para buscar los caramelos que deben explotar
        //guardando en una matriz aux true en caso de que explote y false en el contrario
        //ademas de guardarlo en el vector
        for (int fil = 0; fil < m_ancho; fil++) 
        {
            for (int col = 0; col < m_altura; col++)
            {
                Candy* c = m_matriz[fil][col];
                if (m_matriz[fil][col] != nullptr && shouldExplode(fil, col))
                {
                    auxExplosion[fil][col] = true;
                    caramelosExplotados.push_back(c);
                }
                else
                {
                    auxExplosion[fil][col] = false;
                }
                    
            }
        }
        
        //bucle que a partir de la matriz auxiliar explota los caramelos 
        for (int fil = 0; fil < m_ancho; fil++)
        {
            for (int col = 0; col < m_altura; col++)
            {
                if (auxExplosion[fil][col] == true)
                {
                    m_matriz[fil][col] = nullptr;
                }
            }
        }

        //bucle encargado de la gravedad, en caso de una celda vacia con un caramelo en la celda 
        //inmediatamente superior, copiara su contendio y luego la que estaba arriba explota, todo esto de abajo a arriba
        for (int fil = m_ancho-1; fil >= 0; fil--)
        {
            for (int col = m_altura-1; col >= 0; col--)
            {
                if (col != 0 && m_matriz[fil][col] == nullptr && m_matriz[fil][col-1] != nullptr)
                {
                    m_matriz[fil][col] = m_matriz[fil][col - 1];
                    m_matriz[fil][col - 1] = nullptr;
                }
            }
        }

        //bucle encargado de comprobar si queda explosiones o caidas pendientes
        //en dicho caso no permitira que la funcion termine 
        for (int fil = m_ancho - 1; fil >= 0; fil--)
        {
            for (int col = m_altura - 1; col >= 0; col--)
            {

                if (shouldExplode(fil, col))
                {
                    sinExplosiones = false;
                }
                    

                if (col != 0 && m_matriz[fil][col] == nullptr && m_matriz[fil][col - 1] != nullptr)
                {
                    sinCaidas = false;
                }
                    
            }
        }
    } while (sinExplosiones == false || sinCaidas == false);
    return caramelosExplotados;
}

Candy candyRed(CandyType::TYPE_RED);
Candy candyGreen(CandyType::TYPE_GREEN);
Candy candyBlue(CandyType::TYPE_BLUE);
Candy candyYellow(CandyType::TYPE_YELLOW);
Candy candyOrange(CandyType::TYPE_ORANGE);
Candy candyPurple(CandyType::TYPE_PURPLE);

bool Board::dump(const std::string& output_path) const
{
    ofstream archivo;
    archivo.open(output_path);

    if (!archivo.is_open())
    {
        return false;
    }
    archivo << m_ancho << " " << m_altura << endl; //para saber el tamañño del tablero al leer

    for (int y = 0; y < m_altura; y++)
    {
        for (int x = 0; x < m_ancho; x++)
        {
            Candy* caramelo = getCell(x, y);

            if (caramelo == nullptr)
            {
                archivo << ". ";
            }
            else
            {
                switch (caramelo->getType()) //la flecha es pq como es un puntero . no sirve para llamar metodos
                {
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


bool Board::load(const std::string& input_path)
{
    ifstream archivo;
    archivo.open(input_path);

    if (!archivo.is_open())
    {
        return false;
    }
    archivo >> m_ancho >> m_altura;

    for (int i = 0; i < DEFAULT_BOARD_WIDTH; i++)
    {
        for (int j = 0; j < DEFAULT_BOARD_HEIGHT; j++)
        {
            m_matriz[i][j] = nullptr;
        }
    }
    
    for (int y = 0; y < m_altura; y++)
    {
        for (int x = 0; x < m_ancho; x++)
        {
            char caracter;
            archivo >> caracter; 

            if (caracter == '.')
            {
                m_matriz[x][y] = nullptr;
            }
            else
            {
                switch (caracter)
                {
                    case 'R':
                    {
                        m_matriz[x][y] = &candyRed;
                        break;
                    }     
                    case 'G':
                    {
                        m_matriz[x][y] = &candyGreen;
                        break;
                    }
                    case 'Y':
                    {
                        m_matriz[x][y] = &candyYellow;
                        break;
                    }
                    case 'B':
                    {
                        m_matriz[x][y] = &candyBlue;
                        break;
                    }
                    case 'P':
                    {
                        m_matriz[x][y] = &candyPurple;
                        break;
                    }
                    case 'O':
                    {
                        m_matriz[x][y] = &candyOrange;
                        break;
                    }
                    default:
                    {
                        m_matriz[x][y] = nullptr;
                        break;
                    }
                }
            }
        }
    }
    
    archivo.close();
    
    return true;
}
