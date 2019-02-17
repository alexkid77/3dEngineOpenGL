#ifndef BEZIER_H
#define BEZIER_H
#include "q3loader.h"

class bezier
{
private:
	int                 level;
	std::vector<TVertex>       vertex;
	std::vector<unsigned int>       indexes;
	std::vector<int>        trianglesPerRow;
	std::vector<unsigned int>      rowIndexes;

public:
	TVertex             controls[9];

	void tessellate(int level);
	void render();

	bezier(void);
	~bezier(void);
};
#endif