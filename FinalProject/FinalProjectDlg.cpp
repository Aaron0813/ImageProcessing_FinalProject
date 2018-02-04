
// FinalProjectDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "FinalProject.h"
#include "FinalProjectDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
IplImage* planes[3] = { 0, 0, 0 };  // 多个图像面
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CFinalProjectDlg 对话框

CFinalProjectDlg::CFinalProjectDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFinalProjectDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

}

void CFinalProjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CFinalProjectDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CFinalProjectDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &CFinalProjectDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CFinalProjectDlg 消息处理程序

BOOL CFinalProjectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CFinalProjectDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CFinalProjectDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CFinalProjectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//Open Button的代码
void CFinalProjectDlg::OnBnClickedButton1()
{
	//消息处理机制
	static MSG msg;

	/*     if( argc == 1 || (argc == 2 && strlen(argv[1]) == 1 && isdigit(argv[1][0])))
	capture = cvCaptureFromCAM( argc == 2 ? argv[1][0] - '0' : 0 );
	else if( argc == 2 )
	capture = cvCaptureFromAVI( argv[1] ); */
	//capture = cvCaptureFromAVI( "3.avi" );  

	capture = cvCaptureFromCAM(0);

	if (!capture)
	{
		fprintf(stderr, "Could not initialize capturing.../n");
		return;
	}

	IplImage* faceRecognize = 0;
	IplImage* forgroundExtract = 0;
	BackgroundSubtractorMOG mog;

	while (bInLoop)
	{
		//防止UI阻塞  响应前端
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			continue;
		}
		IplImage* frame = 0;
		Mat image;
		Mat image02;
		 
		//从摄像头或者文件中抓取并返回一帧  
		//若返回值为NULL，说明到了视频的最后一帧。  
		frame = cvQueryFrame(capture);
		if (!frame)
			break;
		image = (cv::Mat(frame, true)).clone();
		image02 = image.clone();

		LaplaceConvertion(frame, laplace);
		faceRecognize = FaceRecognization(image);
		forgroundExtract = ForegroundExtract(image02, mog);
		DrawPicToHDC(frame, IDC_STATIC_01);
		DrawPicToHDC(colorlaplace, IDC_STATIC_02);
		DrawPicToHDC(faceRecognize, IDC_STATIC_03);
		DrawPicToHDC(forgroundExtract, IDC_STATIC_04);

	} 


	cvReleaseCapture(&capture);
	//CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)startlop, NULL, 0, 0);
	/*
	while (bInLoop)
	{
		IplImage* frame = 0;
		Mat image;
		Mat image02;
		//cvQueryFrame  
		//  
		//从摄像头或者文件中抓取并返回一帧  
		//IplImage* cvQueryFrame( CvCapture* capture );  
		//capture   
		//视频获取结构。  
		//函数cvQueryFrame从摄像头或者文件中抓取一帧，然后解压并返回这一帧。  
		//这个函数仅仅是函数cvGrabFrame和函数cvRetrieveFrame在一起调用的组合。  
		//返回的图像不可以被用户释放或者修改。 抓取后，capture被指向下一帧，  
		//可用cvSetCaptureProperty调整capture到合适的帧。  
		//  
		//注意： cvQueryFrame返回的指针总是指向同一块内存。建议cvQueryFrame后拷贝一份  
		//。而且返回的帧需要FLIP后才符合OPENCV的坐标系。 若返回值为NULL，说明到了视频的最后一帧。  
		frame = cvQueryFrame(capture);
		if (!frame)
			break;
		image = (cv::Mat(frame,true)).clone();
		image02 = image.clone();
		
		LaplaceConvertion(frame, laplace);
		faceRecognize = FaceRecognization(image);
		forgroundExtract = ForegroundExtract(image02, mog);
		DrawPicToHDC(frame, IDC_STATIC_01);
		DrawPicToHDC(colorlaplace, IDC_STATIC_02);
		DrawPicToHDC(faceRecognize, IDC_STATIC_03);
		DrawPicToHDC(forgroundExtract, IDC_STATIC_04);
				
	}*/
	
	
}

void CFinalProjectDlg::DrawPicToHDC(IplImage *img, UINT ID)
{
	CDC *pDC = GetDlgItem(ID)->GetDC();
	HDC hDC = pDC->GetSafeHdc();
	CRect rect;
	GetDlgItem(ID)->GetClientRect(&rect);
	CvvImage cimg;
	cimg.CopyOf(img); // 复制图片
	cimg.DrawToHDC(hDC, &rect); // 将图片绘制到显示控件的指定区域内
	ReleaseDC(pDC);
}

void CFinalProjectDlg::LaplaceConvertion(IplImage* frame, IplImage* laplace)
{
	int i;
	if (!laplace)
	{
		for (i = 0; i < 3; i++)
			planes[i] = cvCreateImage(cvSize(frame->width, frame->height), 8, 1);
		laplace = cvCreateImage(cvSize(frame->width, frame->height),
			IPL_DEPTH_16S, 1);
		colorlaplace = cvCreateImage(cvSize(frame->width, frame->height), 8, 3);
	}
	cvCvtPixToPlane(frame, planes[0], planes[1], planes[2], 0);
	for (i = 0; i < 3; i++)
	{
		
		//计算图像的 Laplacian 变换  
		//核大小 (与 cvSobel 中定义一样).  
		cvLaplace(planes[i], laplace, 3); // 3: aperture_size  
	
		//使用线性变换转换输入数组元素成8位无符号整型  
		//原数组元素按比例缩放后添加的值。  
		//函数 cvConvertScaleAbs 与前一函数是相同的，但它是存贮变换结果的绝对值：  
		//dst(I)=abs(src(I)*scale + (shift,shift,...))  
		//函数只支持目标数数组的深度为 8u (8-bit 无符号) , 对于别的类型函数仿效于cvConvertScale 和 cvAbs 函数的联合  
		cvConvertScaleAbs(laplace, planes[i], 1, 0);  // planes[] = ABS(laplace)  
	}
	//cvCvtPixToPlane是cvCvtPlaneToPix的逆函数  
	cvCvtPlaneToPix(planes[0], planes[1], planes[2], 0, colorlaplace);
	colorlaplace->origin = frame->origin;   //让他们结构一致  
}


IplImage* CFinalProjectDlg::FaceRecognization(Mat image)
{
	//Mat image;//视频流的图像或者图片  
	bool tryflip = false;//首先不尝试翻转  
	CascadeClassifier cascade, nestedCascade;//分类器  
	double scale = 4;//规模=1  
	IplImage* result=0;
	if (!cascade.load(cascadeName))
	{
		cerr << "ERROR: Could not load classifier cascade" << endl;
		return NULL;
	}
	
	// 循环捕捉，直到用户按键跳出循环体    
	if (!image.empty())
	{
		result = DetectAndDraw(image, cascade, nestedCascade, scale, tryflip);
		cout << "123123" << endl;
	}

	return result;
}
IplImage* CFinalProjectDlg::DetectAndDraw(Mat& img, CascadeClassifier& cascade, CascadeClassifier& nestedCascade, double scale, bool tryflip)
{
	//IplImage *iplimg = 0;
	int i = 0;
	double t = 0;
	vector<Rect> faces, faces2;//翻转前的脸face，翻转后的脸face2  
	const static Scalar colors[] = { CV_RGB(0, 0, 255), CV_RGB(0, 128, 255), CV_RGB(0, 255, 255), CV_RGB(0, 255, 0),
		CV_RGB(255, 128, 0), CV_RGB(255, 255, 0), CV_RGB(255, 0, 0), CV_RGB(255, 0, 255) };//用于标识人脸的圈圈的颜色  
	Mat gray, smallImg(cvRound(img.rows / scale), cvRound(img.cols / scale), CV_8UC1);//cvRound对一个double型的数进行四舍五入，并返回一个整型数  
	cvtColor(img, gray, COLOR_BGR2GRAY);//变成灰度  
	resize(gray, smallImg, smallImg.size(), 0, 0, INTER_LINEAR);//双线性插值（默认方法）  
	equalizeHist(smallImg, smallImg);//使灰度图象直方图均衡化,增强图像的亮度及对比度  

	t = (double)cvGetTickCount();//得到现在的时间  
	cascade.detectMultiScale(smallImg, faces,
		1.1, 2, 0
		//|CASCADE_FIND_BIGGEST_OBJECT  
		//|CASCADE_DO_ROUGH_SEARCH  
		| CASCADE_SCALE_IMAGE
		,
		Size(30, 30));
	if (tryflip)
	{
		flip(smallImg, smallImg, 1);
		cascade.detectMultiScale(smallImg, faces2,
			1.1, 2, 0
			//|CASCADE_FIND_BIGGEST_OBJECT  
			//|CASCADE_DO_ROUGH_SEARCH  
			| CASCADE_SCALE_IMAGE
			,
			Size(30, 30));
		for (vector<Rect>::const_iterator r = faces2.begin(); r != faces2.end(); r++)
		{
			faces.push_back(Rect(smallImg.cols - r->x - r->width, r->y, r->width, r->height));
		}
	}
	t = (double)cvGetTickCount() - t;//得出识别所用的时间  
	printf("detection time = %g ms\nthe number of faces = %d\n", t / ((double)cvGetTickFrequency()*1000.), faces.size());
	for (vector<Rect>::const_iterator r = faces.begin(); r != faces.end(); r++, i++)//画圈圈  
	{
		Mat smallImgROI;
		vector<Rect> nestedObjects;
		Point center;
		Scalar color = colors[i % 8];
		int radius;

		double aspect_ratio = (double)r->width / r->height;
		if (0.75 < aspect_ratio && aspect_ratio < 1.3)
		{
			center.x = cvRound((r->x + r->width*0.5)*scale);
			center.y = cvRound((r->y + r->height*0.5)*scale);
			radius = cvRound((r->width + r->height)*0.25*scale);
			circle(img, center, radius, color, 3, 8, 0);
		}
		else
			rectangle(img, cvPoint(cvRound(r->x*scale), cvRound(r->y*scale)),
			cvPoint(cvRound((r->x + r->width - 1)*scale), cvRound((r->y + r->height - 1)*scale)),
			color, 3, 8, 0);
		if (nestedCascade.empty())
			continue;
		smallImgROI = smallImg(*r);
		nestedCascade.detectMultiScale(smallImgROI, nestedObjects,
			1.1, 2, 0
			//|CASCADE_FIND_BIGGEST_OBJECT  
			//|CASCADE_DO_ROUGH_SEARCH  
			//|CASCADE_DO_CANNY_PRUNING  
			| CASCADE_SCALE_IMAGE
			,
			Size(30, 30));
		for (vector<Rect>::const_iterator nr = nestedObjects.begin(); nr != nestedObjects.end(); nr++)
		{
			center.x = cvRound((r->x + nr->x + nr->width*0.5)*scale);
			center.y = cvRound((r->y + nr->y + nr->height*0.5)*scale);
			radius = cvRound((nr->width + nr->height)*0.25*scale);
			circle(img, center, radius, color, 3, 8, 0);
		}
	}

	//深拷贝
	IplImage imgTmp = img;
	IplImage *input = cvCloneImage(&imgTmp);
	return input;
}

IplImage* CFinalProjectDlg::ForegroundExtract(Mat image, BackgroundSubtractorMOG &mog)
{
	Mat foreground;	// 前景图片
	// 混合高斯物体
	
	
		// 更新背景图片并且输出前景
		mog(image, foreground, 0.01);
		// 输出的前景图片并不是2值图片，要处理一下显示 
		threshold(foreground, foreground, 128, 255, THRESH_BINARY_INV);
		// show foreground
		//imshow("Extracted Foreground", foreground);

	IplImage imgTmp = foreground;
	IplImage *input = cvCloneImage(&imgTmp);
	return input;
}

void CFinalProjectDlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	bInLoop = false;
	CDialogEx::OnOK();
}
