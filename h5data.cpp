#include <iostream>
#include "h5data.h"
#include <xmmintrin.h>

using namespace std;
using namespace H5;

Data::Data(const char *filename){

	Data::read(filename,"data");	

}

Data::Data(const char *filename,const char *dataname){

	Data::read(filename,dataname);	

}

Data::~Data(){

	free(data16);
	delete[] dims;
}

int Data::read(const char *filename,const char *dataname){

	int rank,n;

	H5File file(filename, H5F_ACC_RDONLY);

	DataSet dataset = file.openDataSet(dataname);
	DataSpace dataspace = dataset.getSpace();

	rank = dataspace.getSimpleExtentNdims();

	dims = new hsize_t[rank];
	ndims = dataspace.getSimpleExtentDims(dims, NULL);

	n = dims[0] * dims[1] * dims[2];
	data16 = static_cast<float *>(aligned_alloc(16, sizeof(float) * n));

	dataset.read(data16, PredType::NATIVE_FLOAT);

	dataspace.close();
	dataset.close();
	file.close();

	for(int i = 0; i < ndims; i++){
		cout << i << " : " << dims[i] << "\n";
	}

	return 0;

}

SliceAndDice::SliceAndDice(Data *data)
{

	n_pixel = data->dims[0] * data->dims[1];

	datacube = data;	
	
	image_data = static_cast<float *>(aligned_alloc(16, sizeof(float) * n_pixel));
	image = new QImage(data->dims[1],data->dims[0],QImage::Format_RGB32);

}

SliceAndDice::SliceAndDice(Data *data,int channel)
{

	n_pixel = data->dims[0] * data->dims[1];

	datacube = data;	
	
	image_data = static_cast<float *>(aligned_alloc(16, sizeof(float) * n_pixel));
	image = new QImage(data->dims[1],data->dims[0],QImage::Format_RGB32);

	slice(channel);
	dice();

}

int SliceAndDice::slice(int channel)
{

	int off = datacube->dims[2];
	float pixel;
	image_max = 0;

	for(int i=0; i < n_pixel; i++){

		pixel = *(datacube->data16 + i * off + channel);

		if(pixel > image_max){
			image_max = pixel;
		}
		image_data[i] = pixel;

	}

	return 0;
}

int SliceAndDice::dice()
{
	QRgb value;
	float pixel;

	int x = datacube->dims[1];
	int y = datacube->dims[0];

	for(int i=0; i < x; i++){
		for(int j=0; j< y; j++){

			pixel = (image_data[ j * x + i] * 255) / image_max;
			value = qRgb(pixel,pixel,pixel);

			image->setPixel(i,j,value);
		}
	}

	pix = pix.fromImage(*image);

	return 0;
}

int SliceAndDice::slicedice(int channel)
{
	slice(channel);
	dice();

	return 0;
}

float* SliceAndDice::get_pixel(int x, int y)
{

	return datacube->data16 + datacube->dims[2] * (y * datacube->dims[1] + x);

}
