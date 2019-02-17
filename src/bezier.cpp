#include "bezier.h"

bezier::bezier(void)
{
}

bezier::~bezier(void)
{
}
void bezier::tessellate(int L) {
    level = L;

    // The number of vertices along a side is 1 + num edges
    const int L1 = L + 1;

    vertex.resize(L1 * L1);

    // Compute the vertices
    int i;

    for (i = 0; i <= L; ++i) {
        double a = (double)i / L;
        double b = 1 - a;

        vertex[i] =
            controls[0] * (b * b) + 
            controls[3] * (2 * b * a) +
            controls[6] * (a * a);
    }

    for (i = 1; i <= L; ++i) {
        double a = (double)i / L;
        double b = 1.0 - a;

        TVertex temp[3];

        int j;
        for (j = 0; j < 3; ++j) {
            int k = 3 * j;
            temp[j] =
                controls[k + 0] * (b * b) + 
                controls[k + 1] * (2 * b * a) +
                controls[k + 2] * (a * a);
        }

        for(j = 0; j <= L; ++j) {
            double a = (double)j / L;
            double b = 1.0 - a;

            vertex[i * L1 + j]=
                temp[0] * (b * b) + 
                temp[1] * (2 * b * a) +
                temp[2] * (a * a);
        }
    }


    // Compute the indices
    int row;
    indexes.resize(L * (L + 1) * 2);

    for (row = 0; row < L; ++row) {
        for(int col = 0; col <= L; ++col)	{
            indexes[(row * (L + 1) + col) * 2 + 1] = row       * L1 + col;
            indexes[(row * (L + 1) + col) * 2]     = (row + 1) * L1 + col;
        }
    }

    trianglesPerRow.resize(L);
    rowIndexes.resize(L);
    for (row = 0; row < L; ++row) {
        trianglesPerRow[row] = 2 * L1;
        rowIndexes[row]      = indexes[row * 2 * L1];
    }
    
}
void bezier::render() {
   
}