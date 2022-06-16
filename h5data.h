#ifndef H5DATA_H
#define H5DATA_H

#include <H5Cpp.h>
#include <QMainWindow>

class Data
{
	public:
		int ndims;
		hsize_t *dims;
		float *data16;

		int read(const char*, const char*);
		Data(const char*);
		Data(const char*, const char*);

		~Data();
};

class SliceAndDice
{
	public:

		int n_pixel;
		float *image_data;
		float image_max;

		Data *datacube;

		QImage *image;
		QPixmap pix;

		SliceAndDice(Data*);
		SliceAndDice(Data*,int);

		int slicedice(int);
		int slice(int);
		int dice();

		float *get_pixel(int,int);
};
#endif 
