#include <opencv2/core/core.hpp>  
#include<opencv2/highgui/highgui.hpp>  
#include <opencv2/nonfree/features2d.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#include "opencv2/features2d/features2d.hpp"
#include<opencv2/legacy/legacy.hpp>
#include<list>


using namespace cv; 
class Detect
{
public:
	 Detect(Mat *srcimg,Mat *destImg);
	 ~Detect();
	 void  GetSrcPointVector();
	 void  GetDestPointVector();
	 void  StartDetect();
	 void  SetMinHession(int minhes);
	 int   GetMinHession()const;
	 void  DrawDestKeyPoint(Mat  &tempmat);
	 void  DrawSrcKeyPoint(Mat &tempmat);
	 int   GetDestKeyPointCount()const;
	 int   GetSrcKeyPointCount()const;
	 int   GetMatchesCount()const;
	 void  StartMatch();
	 BOOL  CalRect(std::vector<KeyPoint> &keypoint,std::vector<CRect> &rects);
	 BOOL  CalRect(std::vector<DMatch> &matchvector,std::vector<KeyPoint>&keypoints,std::vector<CRect> &Rects);
	 BOOL  CalRect(std::vector<DMatch> &matchvector,std::vector<CRect> &rects); 
	
	 void Bubble(vector<int>& avector);
	 int destRectCount;//ceshiyong
	 BOOL ZeroDetect(std::vector<int> avector);
	 Mat srcImage;
	 Mat destImage;

	 std::vector<CRect> destRects;
	 std::vector<CRect> srcRects;

	 int srcwidth;//测试用，可以删掉
	 int srcheight;//测试用，最后可以删掉
	 BOOL re;//test
private:
	std::vector<KeyPoint> srcKeyPoint;
	std::vector<KeyPoint> destKeyPoint;//vector模板类，存放任意类型的动态数组
	std::vector<CPoint> srcPoint;
	std::vector<CPoint> destPoint;
	int minHession;//SURF算法中的hessian阈值
	std::vector< DMatch > matches;  
	


};

