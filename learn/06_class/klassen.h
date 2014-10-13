#ifndef __KLASSEN_H__
#define __KLASSEN_H__

class raumschiff
{
	public:

	int x;
	int y;
	int leben;
	
	void printLeben(void);
	void crash(void);

	// Konstruktor
	raumschiff(int pos_x, int pos_y, int leb);
	raumschiff(int pos_x, int pos_y);
	raumschiff(void);
	
	// Destruktor
	~raumschiff();
};

#endif
