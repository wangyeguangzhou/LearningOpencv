
#include<stdafx.h>
#include "Detect.h"
#include <opencv2/core/core.hpp>  
#include<opencv2/highgui/highgui.hpp>  
#include <opencv2/nonfree/features2d.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#include "opencv2/features2d/features2d.hpp"
#include<opencv2/legacy/legacy.hpp>
#include<list>
//#include <stdafx.h>
using namespace cv; 

 Detect::Detect(Mat *srcimg,Mat *destImg)
{
	if(!srcimg->data||!destImg->data)return;
	srcimg->copyTo(srcImage);
	destImg->copyTo(destImage);
	 minHession=200; //默认值为200
}
 void Detect::StartDetect()
 {
	 //【2】使用SURF算子检测关键点  
	 SurfFeatureDetector detector(minHession );//定义一个SurfFeatureDetector（SURF） 特征检测类对象    
	 //【3】调用detect函数检测出SURF特征关键点，保存在vector容器中  
	
	 detector.detect( destImage, destKeyPoint );  
	 detector.detect( srcImage, srcKeyPoint );  
	 //testcode
	  re=CalRect(srcKeyPoint,srcRects);
	  if(re)
	  {
		  srcwidth=srcRects[0].Width();
		  srcheight=srcRects[0].Height();
	  }
	
 }

 void Detect::StartMatch()//可以考虑加一个进度条来反映匹配的进度
 {
	 //【4】计算描述符（特征向量）  
	 SurfDescriptorExtractor extractor;  

	 //循环匹配
	 //结束条件是选择 查询图像的特征点数为空还是选择特征点数小于模板图的特征点数好呢？
	 //先用小于特征点数来做，看效果
	 while (destKeyPoint.size()>srcKeyPoint.size())
	 {
	 Mat descriptors1, descriptors2;  
	 extractor.compute( srcImage,srcKeyPoint, descriptors1 );  
	 extractor.compute( destImage, destKeyPoint, descriptors2 );  
	  //可以将srcImage特征点的点坐标抽取出来
	  //【5】使用BruteForce进行匹配  
	  // 实例化一个匹配器  
	  BruteForceMatcher< L2<float> > matcher;  
	  //匹配两幅图中的描述子（descriptors）  
	  matcher.match( descriptors1, descriptors2, matches );  
	  //匹配之后计算并保存匹配区域的矩形
	  descriptors1.release();
	  descriptors2.release();
	 if(!CalRect(matches,destKeyPoint,destRects))break;
	 }
	 destRectCount=destRects.size();
 }
 void Detect::DrawDestKeyPoint(Mat &tempmat)
 {
	 if(0==destKeyPoint.size())return;

		 drawKeypoints( destImage, destKeyPoint, tempmat, Scalar::all(-1), DrawMatchesFlags::DEFAULT ); 
	

 }
 void Detect::DrawSrcKeyPoint(Mat &tempmat)
 {
	 if(0==srcKeyPoint.size())return;
	  drawKeypoints( srcImage, srcKeyPoint, tempmat, Scalar::all(-1), DrawMatchesFlags::DEFAULT ); 
 }
 Detect::~Detect()
 {
	 srcImage.release();
	 destImage.release();
	 srcKeyPoint.swap(std::vector<KeyPoint>());//释放vector的内存，否则程序结束的时候回会报错
	 destKeyPoint.swap(std::vector<KeyPoint>());
	 matches.swap(std::vector< DMatch > ());
	 destRects.swap(std::vector<CRect>());
	 srcRects.swap(std::vector<CRect>());
 }
 int Detect::GetDestKeyPointCount()const
 {
	 return destKeyPoint.size();
 }
 int Detect::GetSrcKeyPointCount()const
 {
	 return srcKeyPoint.size();
 
 }
 void Detect::SetMinHession(int minhes)
 {

	 minHession=minhes;
 }
 int  Detect::GetMinHession()const
 {
	 return minHession;
 }
 int Detect::GetMatchesCount()const
 {
	 return matches.size();
 }
 BOOL Detect::CalRect(std::vector<KeyPoint> &keypoint,std::vector<CRect> &rects)
 {
	 //查找特征点的最大最小横纵坐标组成这个特征点所占据的矩形区域
	 int xmin=INT_MAX;
	 int ymin=INT_MAX;//这组最小坐标点将作为矩形的起点
	 int xmax=INT_MIN;
	 int ymax=INT_MIN;//通过最大最小坐标点计算矩形的宽度和高度

	 vector<KeyPoint>::iterator iter;
	 //查找最值
	 for(iter=keypoint.begin();iter!=keypoint.end();iter++)
	 {
		 int tempx=(iter->pt.x);
		 int tempy=(iter->pt.y);
		 if(tempx<=xmin)xmin=tempx;//换成三元表达式更简洁，下次改
		 if(tempx>=xmax)xmax=tempx;
		 if(tempy<=ymin)ymin=tempy;
		 if(tempy>=ymax)ymax=tempy;
	 }
	 if((xmin==xmax)||(ymin==ymax))return FALSE;//判断这个矩形是否为空
	 ////计算Crect参数
	 rects.push_back( CRect (xmin,ymin,xmax,ymax));
	 return TRUE;
 }
 //////////////////////////////////////////////////////////////////////////
 /*
 该函数第二个参数只能输入查询图像，不能输入模板图像。
 函数BOOLCalRect(std::vector<DMatch> &matchvector,std::vector<KeyPoint>&keypoints,std::vector<CRect> &Rects)
 输入参数为匹配向量和关键点向量以及矩形向量
 按照匹配向量中对应的关键点坐标将模板图像的特征点中已经识别的点删除掉。
 */
 //////////////////////////////////////////////////////////////////////////
 BOOL Detect::CalRect(std::vector<DMatch> &matchvector,std::vector<KeyPoint>&keypoints,std::vector<CRect> &Rects)
 {
	 //查找特征点的最大最小横纵坐标组成这个特征点所占据的矩形区域
	 int xmin=INT_MAX;
	 int ymin=INT_MAX;//这组最小坐标点将作为矩形的起点
	 int xmax=INT_MIN;
	 int ymax=INT_MIN;//通过最大最小坐标点计算矩形的宽度和高度
	
	 //查找最值并删除对应的点
    std::vector<DMatch>::iterator iter;
	std::vector<int> forSort;
	 for(iter=matchvector.begin();iter!=matchvector.end();iter++)
	 {
		 int tempx=(keypoints[iter->trainIdx].pt.x);
		 int tempy=(keypoints[iter->trainIdx].pt.y);
		 if(tempx<=xmin)xmin=tempx;//换成三元表达式更简洁，下次改
		 if(tempx>=xmax)xmax=tempx;
		 if(tempy<=ymin)ymin=tempy;
		 if(tempy>=ymax)ymax=tempy;
		 forSort.push_back(iter->trainIdx);
	 }
	 //对列表中的索引号排序
	 Bubble(forSort);
	 //判断序列表中有两个以及两个以上的0时，返回false，并停止匹配
	 if( ZeroDetect(forSort))return FALSE;
	 //逐项减去一个值
	 int isub=0;
	 for (std::vector<int>::iterator it=forSort.begin();it!=forSort.end();it++,isub++)
	 {
		 *it-=isub;
	 }
	 //利用上面的forSort 删除keypoints中对应的点
	 for (std::vector<int>::iterator itor=forSort.begin();itor!=forSort.end();itor++)
	 {
		 keypoints.erase(keypoints.begin()+*itor);
	 }
	  forSort.swap(std::vector<int>());
	 if((xmin!=xmax)&&(ymin!=ymax))//判断这个矩形是否为空
	 {
		 Rects.push_back( CRect (xmin,ymin,xmax,ymax));
	 }
	 return TRUE;
 }
 BOOL Detect::CalRect(std::vector<DMatch> &matchvector,std::vector<CRect> &rects)
 {
	

	  return FALSE;
 }

void Detect::Bubble(vector<int>& avector)
{
	if(avector.size()<=1)return;
		for (int i = 0; i <avector.size()-1; i++)
		{
			for (int j = 0; j < avector.size()- 1 - i; j++)
			{
				/*int temp1=avector[j];
				int temp2=avector[j+1];*/
				if (avector[j]>avector[j+1])//(temp1>temp2)
				{
					int temp = avector[j + 1];
					avector[j + 1] = avector[j];
					avector[j] = temp;
				}
			}
		}
}
BOOL Detect::ZeroDetect(std::vector<int> avector)
{
	int temp=0;
	for (std::vector<int>::iterator it=avector.begin();it!=avector.end();it++)
	{
		if(0 ==*it)temp++;
	}
	if(temp>1)return TRUE;
	return FALSE;
}