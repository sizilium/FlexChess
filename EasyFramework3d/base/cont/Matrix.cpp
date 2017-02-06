#include <vs/base/cont/Matrix.hpp>
#include <cmath>
#include <cstdlib>

namespace vs
{
namespace base
{
namespace cont
{


Matrix<int> convertMatrixToAdjacencyMatrix(const Matrix<int> &matrix)
{
    int size = matrix.numRows() * matrix.numRows();

    // rückgabe matrix anlegen (quadratische groesse der eingabe matrix)
    Matrix<int> retMatrix(size, size);

    // alle "start" knoten durchlaufen
    for (int i = 0; i < retMatrix.numRows(); i++)
    {
        // alle "ziel" knoten durchlaufen
        for (int j = 0; j < retMatrix.numRows(); j++)
        {
            // gewichte von start und ziel feld bestimmen
            int weight1, weight2;
            div_t res1 = div(i, matrix.numColumns() );
            div_t res2 = div(j, matrix.numColumns() );

            weight1 = matrix.get(res1.quot, res1.rem);
            weight2 = matrix.get(res2.quot, res2.rem);

            // sind gewichte -1 ist feld unpassierbar
            if (weight1 < 0 || weight2 < 0)
            {
                retMatrix.set(-1, i, j);
                continue;
            }

            // ist abstand von start und ziel feld groesser 1 (also nicht direkt
            // erreichbar) -1 eintragen
            if (abs(i%(matrix.numColumns()) - j%(matrix.numColumns()) ) > 1 ||
                abs(i/matrix.numColumns() - j/matrix.numColumns()) > 1)
            {
                retMatrix.set(-1, i, j);
                continue;
            }

            if (i == j)
                continue;   // an dieser steht schon stelle 0

            retMatrix.set(weight1 + weight2, i, j);
        }
    }

    return retMatrix;
}


} // cont
} // base
} // vs
