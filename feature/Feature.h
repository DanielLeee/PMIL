//////////////////////////////////////////////////////////////////////////
//Function: Implement Different Feature Descriptor 
//Author: Junyan Zhu, Technology Strategy 
//Date: created @ 20110623
//////////////////////////////////////////////////////////////////////////
#pragma once

#include "config.h"
#include "GLCM.h"

class CFeature
{
public: 
	//construction based on feature config File 
	CFeature(string configFileName); 
	//deconstruction 
	~CFeature(); 
	//Get the features of an image
	float* GetFeatures(const Mat inputImage);
	//Get the feature length 
	int GetFeatureLength(); 

private:
	
	//////////////////////////////////////////////////////////////////////////
	//Different Feature Descriptor 	
	void ComputeSIFTDescriptor(const Mat grayImg, float* ftrs, int& offset); 	
	void ComputeColorDescriptor(const Mat LUVImg, float* ftrs, int& offset);	
	void ComputeGrayHistogram(const Mat grayImg, float* ftrs, int& offset); 	
	void ComputeLABHistogram(const Mat LABImg, float* ftrs, int& offset); 	
	void ComputeHOGDescriptor(const Mat grayImg, float* ftrs, int& offset); 		
	void ComputeGLCMFeatures(const Mat grayImg, float* ftrs, int& offset); 
	void ComputeREGIONFeatures(const Mat grayImg, float* ftrs, int& offset); 
	
	//////////////////////////////////////////////////////////////////////////
	//Others: 
	void ReadParamters(string configFileName); 
	//////////////////////////////////////////////////////////////////////////
	//Fast mathematic implementation 
	//Output = input mod 2pi 
	float fast_mod_2pi(float x); 

	//////////////////////////////////////////////////////////////////////////
	//Tools
	//Compute main direction for a point
	float ComputeMainDirection(const Mat oriImg);	
	//Compute the length of feature 
	int ComputeFeatureLength(); 
	//Normalize a vector
	void NormalizeVector(float* v, int vSize);
	//Clear variables 
	void Clear(void);	
	//Set feature Name 
	void SetFtrNames(void); 
	//Low Case
	string Lowcase(string src); 

private: 
	vector<bool> m_isUsedVec; 
	vector<string> m_ftrNameVec; 
	
	string m_ftrFileName; 
	string m_haarPath; 		
	bool m_isAlignAngle; 

public:
	int m_patchSize;
	int m_trainStep;
	int m_testStep;
	int m_trainRate;
	int m_testRate;

private:
	int m_numFtrs;
	int m_SIFTLayer; 	 
	int m_HISTBins; 
	int m_HOGCellSize; 
	int m_HOGNBins; 	
	int m_LABLBins; 
	int m_LABaBins; 
	int m_LABbBins; 	
	int m_GLCMDis;
	int m_GLCMGrayLevel;
	int m_REGIONThr;
	int m_REGIONBound;
	ZBGLCM glcm;

private: 
	static const int COLOR_FEATURE_LENGTH = 6; 
	static const int SIFT_FEATURE_LENGTH = 128; 
	static const int NUM_FEATURE_TYPE = 7;

	enum FeatureType
	{
		FTRTYPE_COLOR	= 0, 
		FTRTYPE_SIFT	= 1,		 
		FTRTYPE_HIST	= 2, 		
		FTRTYPE_HOG		= 3, 				
		FTRTYPE_LAB		= 4,
		FTRTYPE_GLCM	= 5,
		FTRTYPE_REGION  = 6
	};
};
