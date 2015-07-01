
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
	 minHession=200; //Ĭ��ֵΪ200
}
 void Detect::StartDetect()
 {
	 //��2��ʹ��SURF���Ӽ��ؼ���  
	 SurfFeatureDetector detector(minHession );//����һ��SurfFeatureDetector��SURF�� ������������    
	 //��3������detect��������SURF�����ؼ��㣬������vector������  
	
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

 void Detect::StartMatch()//���Կ��Ǽ�һ������������ӳƥ��Ľ���
 {
	 //��4������������������������  
	 SurfDescriptorExtractor extractor;  

	 //ѭ��ƥ��
	 //����������ѡ�� ��ѯͼ�����������Ϊ�ջ���ѡ����������С��ģ��ͼ�������������أ�
	 //����С������������������Ч��
	 while (destKeyPoint.size()>srcKeyPoint.size())
	 {
	 Mat descriptors1, descriptors2;  
	 extractor.compute( srcImage,srcKeyPoint, descriptors1 );  
	 extractor.compute( destImage, destKeyPoint, descriptors2 );  
	  //���Խ�srcImage������ĵ������ȡ����
	  //��5��ʹ��BruteForce����ƥ��  
	  // ʵ����һ��ƥ����  
	  BruteForceMatcher< L2<float> > matcher;  
	  //ƥ������ͼ�е������ӣ�descriptors��  
	  matcher.match( descriptors1, descriptors2, matches );  
	  //ƥ��֮����㲢����ƥ������ľ���
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
	 srcKeyPoint.swap(std::vector<KeyPoint>());//�ͷ�vector���ڴ棬������������ʱ��ػᱨ��
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
	 //����������������С����������������������ռ�ݵľ�������
	 int xmin=INT_MAX;
	 int ymin=INT_MAX;//������С����㽫��Ϊ���ε����
	 int xmax=INT_MIN;
	 int ymax=INT_MIN;//ͨ�������С����������εĿ�Ⱥ͸߶�

	 vector<KeyPoint>::iterator iter;
	 //������ֵ
	 for(iter=keypoint.begin();iter!=keypoint.end();iter++)
	 {
		 int tempx=(iter->pt.x);
		 int tempy=(iter->pt.y);
		 if(tempx<=xmin)xmin=tempx;//������Ԫ���ʽ����࣬�´θ�
		 if(tempx>=xmax)xmax=tempx;
		 if(tempy<=ymin)ymin=tempy;
		 if(tempy>=ymax)ymax=tempy;
	 }
	 if((xmin==xmax)||(ymin==ymax))return FALSE;//�ж���������Ƿ�Ϊ��
	 ////����Crect����
	 rects.push_back( CRect (xmin,ymin,xmax,ymax));
	 return TRUE;
 }
 //////////////////////////////////////////////////////////////////////////
 /*
 �ú����ڶ�������ֻ�������ѯͼ�񣬲�������ģ��ͼ��
 ����BOOLCalRect(std::vector<DMatch> &matchvector,std::vector<KeyPoint>&keypoints,std::vector<CRect> &Rects)
 �������Ϊƥ�������͹ؼ��������Լ���������
 ����ƥ�������ж�Ӧ�Ĺؼ������꽫ģ��ͼ������������Ѿ�ʶ��ĵ�ɾ������
 */
 //////////////////////////////////////////////////////////////////////////
 BOOL Detect::CalRect(std::vector<DMatch> &matchvector,std::vector<KeyPoint>&keypoints,std::vector<CRect> &Rects)
 {
	 //����������������С����������������������ռ�ݵľ�������
	 int xmin=INT_MAX;
	 int ymin=INT_MAX;//������С����㽫��Ϊ���ε����
	 int xmax=INT_MIN;
	 int ymax=INT_MIN;//ͨ�������С����������εĿ�Ⱥ͸߶�
	
	 //������ֵ��ɾ����Ӧ�ĵ�
    std::vector<DMatch>::iterator iter;
	std::vector<int> forSort;
	 for(iter=matchvector.begin();iter!=matchvector.end();iter++)
	 {
		 int tempx=(keypoints[iter->trainIdx].pt.x);
		 int tempy=(keypoints[iter->trainIdx].pt.y);
		 if(tempx<=xmin)xmin=tempx;//������Ԫ���ʽ����࣬�´θ�
		 if(tempx>=xmax)xmax=tempx;
		 if(tempy<=ymin)ymin=tempy;
		 if(tempy>=ymax)ymax=tempy;
		 forSort.push_back(iter->trainIdx);
	 }
	 //���б��е�����������
	 Bubble(forSort);
	 //�ж����б����������Լ��������ϵ�0ʱ������false����ֹͣƥ��
	 if( ZeroDetect(forSort))return FALSE;
	 //�����ȥһ��ֵ
	 int isub=0;
	 for (std::vector<int>::iterator it=forSort.begin();it!=forSort.end();it++,isub++)
	 {
		 *it-=isub;
	 }
	 //���������forSort ɾ��keypoints�ж�Ӧ�ĵ�
	 for (std::vector<int>::iterator itor=forSort.begin();itor!=forSort.end();itor++)
	 {
		 keypoints.erase(keypoints.begin()+*itor);
	 }
	  forSort.swap(std::vector<int>());
	 if((xmin!=xmax)&&(ymin!=ymax))//�ж���������Ƿ�Ϊ��
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