
// FinalProjectDlg.h : ͷ�ļ�
//

#pragma once
#include <opencv2/core/core.hpp>
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "CvvImage.h"
#include <ctype.h>  
#include <stdio.h>
#include <opencv2/video/video.hpp>
#include <opencv2\opencv.hpp>
#include <opencv2\objdetect\objdetect.hpp>  
#include <opencv2\imgproc\imgproc.hpp>  
#include <iostream>  

/*
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/video.hpp>

#include <iostream>
*/
using namespace std;
using namespace cv;


// CFinalProjectDlg �Ի���
class CFinalProjectDlg : public CDialogEx
{
// ����
public:
	CFinalProjectDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_FINALPROJECT_DIALOG };
	 bool bInLoop = true;
	 IplImage* laplace = 0;
	 IplImage* colorlaplace = 0;
	   
	 CvCapture* capture = 0;
	 string cascadeName = "haarcascade_frontalface_alt.xml";
	 string nestedCascadeName = "haarcascade_eye_tree_eyeglasses.xml";

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();

	
	//��Ե���
	 void LaplaceConvertion(IplImage* frame, IplImage* laplace);
	//����ͼƬ
	void DrawPicToHDC(IplImage *img, UINT ID);

	//����ʶ��
	 IplImage* FaceRecognization(Mat image);
	 IplImage* DetectAndDraw(Mat& img, CascadeClassifier& cascade, CascadeClassifier& nestedCascade, double scale, bool tryflip);
	
	//foreground extract
	 IplImage* ForegroundExtract(Mat image, BackgroundSubtractorMOG &mog);

	 //friend LPTHREAD_START_ROUTINE startlop(void*);
	 afx_msg void OnBnClickedOk();
};
