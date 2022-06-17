#ifndef H5DATA_H
#define H5DATA_H

#include <H5Cpp.h>
#include <QMainWindow>

class Datacube
{

	private:

		int ndims;
		int n_pixel;
		float *image_data;
		float image_max;

		QImage *image;

		int slice(int);
		int dice();

	public:

		hsize_t *dims;
		float *data16;

		QPixmap pix;

		int read(const char*, const char*);
		int slicedice(int);

		Datacube(const char*);
		Datacube(const char*, const char*);

		~Datacube();
};

class SliceAndDice
{
	
	private:

		int slice(int);
		int dice();

	public:

		int n_pixel;
		float *image_data;
		float image_max;

		Datacube *datacube;
		QImage *image;
		QPixmap pix;

		SliceAndDice(Datacube*);
		SliceAndDice(Datacube*,int);

		int slicedice(int);

		float *get_pixel(int,int);
};
#endif 
