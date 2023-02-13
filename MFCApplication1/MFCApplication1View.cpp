
// MFCApplication1View.cpp: CMFCApplication1View 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MFCApplication1.h"
#endif
#include<stdlib.h>
#include "MFCApplication1Doc.h"
#include "MFCApplication1View.h"
#define ID_32774 32774
#define ID_32775 32775
#ifdef _DEBUG
#define new DEBUG_NEW


#endif
int ans = 0;// debug
FILE* fp;

Shape* all[100];
int allnum = -1;
int yidongnum = -1;
int now = 0;
// CMFCApplication1View
void draw_all();
IMPLEMENT_DYNCREATE(CMFCApplication1View, CView)

BEGIN_MESSAGE_MAP(CMFCApplication1View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMFCApplication1View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_32771, &CMFCApplication1View::OnDrawCircle)
	ON_COMMAND(ID_32772, &CMFCApplication1View::OnDrawRec)
	ON_COMMAND(ID_32773, &CMFCApplication1View::OnDrawLine)
	ON_COMMAND(ID_32774, &CMFCApplication1View::OnMovePic)
	ON_WM_MOUSEMOVE()
//	ON_WM_MBUTTONDOWN()
	ON_WM_LBUTTONUP()
//ON_WM_MBUTTONDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()

	ON_COMMAND(ID_32775, &CMFCApplication1View::OnSave)
	ON_COMMAND(ID_32776, &CMFCApplication1View::OnRead)
	ON_COMMAND(ID_32777, &CMFCApplication1View::OnDraw_Polygon)
END_MESSAGE_MAP()

// CMFCApplication1View 构造/析构

CMFCApplication1View::CMFCApplication1View() noexcept
{
	// TODO: 在此处添加构造代码

}

CMFCApplication1View::~CMFCApplication1View()
{

}

BOOL CMFCApplication1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMFCApplication1View 绘图

void CMFCApplication1View::OnDraw(CDC* /*pDC*/)
{
	CMFCApplication1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CMFCApplication1View 打印


void CMFCApplication1View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMFCApplication1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMFCApplication1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMFCApplication1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


void CMFCApplication1View::OnRButtonUp(UINT  nFlags , CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}


void CMFCApplication1View::OnContextMenu(CWnd*  pWnd , CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFCApplication1View 诊断

#ifdef _DEBUG
void CMFCApplication1View::AssertValid() const
{
	CView::AssertValid();
}

void CMFCApplication1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCApplication1Doc* CMFCApplication1View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApplication1Doc)));
	return (CMFCApplication1Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCApplication1View 消息处理程序


void CMFCApplication1View::OnDrawCircle()
{
	// TODO: 在此添加命令处理程序代码
	allnum++;
	now = 1;
	My_Circle* circle1=new My_Circle;
	Shape* circle=circle1;

	all[allnum] = circle;
	
}


void CMFCApplication1View::OnDrawRec()
{
	// TODO: 在此添加命令处理程序代码
	allnum++;
	now = 1;
	My_Rectangle* rec1 = new My_Rectangle;
	Shape* rec = rec1;
	all[allnum] = rec;
}


void CMFCApplication1View::OnDrawLine()
{
	// TODO: 在此添加命令处理程序代码
	allnum++;
	now = 1;
	My_Line* line1 = new My_Line;
	Shape* line = line1;
	all[allnum] = line;
}


void CMFCApplication1View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CView::OnMouseMove(nFlags, point);
}





void CMFCApplication1View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	
	if (now == 1 && all[allnum]->flag == -1)
	{
		all[allnum]->point2 = point;
		CDC* pDC1 = GetDC();
		all[allnum]->pDC = pDC1;
		all[allnum]->draw();
		now = 0;
	}
	if (now == 1 && all[allnum]->flag >= 0) {

		all[allnum]->pointnum[all[allnum]->flag] = point;
		all[allnum]->flag = all[allnum]->flag + 1;

	}
	if (now == 3) {
		CDC* pDC1 = GetDC();
		all[allnum]->pDC = pDC1;
		all[yidongnum]->point4 = point;
		all[yidongnum]->Move();
		yidongnum = -1;
		now = -1;
	}
	CView::OnLButtonUp(nFlags, point);
}




void CMFCApplication1View::OnLButtonDown(UINT nFlags, CPoint point)
{
	
	if (now != 1)
		draw_all();
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (now == 1&&all[allnum]->flag==-1) {
		all[allnum]->point1 = point;
	}
	/*if (now == 1 && all[allnum]->flag>=0) {
	
		all[allnum]->pointnum[all[allnum]->flag]= point;
		all[allnum]->flag=all[allnum]->flag+1;

	}*/
	if (now == 2) {
		for (int i = 0; i <= allnum; i++) {
			if (all[i]->judge(point)) {
				all[i]->point3 = point;
				yidongnum = i;
				now = 3;
			}
		}
	}
	CView::OnLButtonDown(nFlags, point);
}


void CMFCApplication1View::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (allnum>=0&&all[allnum]->flag >= 0) {
		CDC* pDC1 = GetDC();
		all[allnum]->pDC = pDC1;
		all[allnum]->draw();
		now = -1;
	}
	CView::OnRButtonDown(nFlags, point);
}


void CMFCApplication1View::OnMovePic()
{
	// TODO: 在此添加命令处理程序代码
	draw_all();
	now = 2;
}


void CMFCApplication1View::OnSave()
{
	// TODO: 在此添加命令处理程序代码
	fp= fopen("outfile.txt", "w+");
	fprintf(fp, "%d\n", allnum);
	
	for (int i = 0; i <= allnum; i++)
	{
		all[i]->fpp = fp;
		all[i]->Save();
	}
	fclose(fp);
}


void CMFCApplication1View::OnRead()
{
	// TODO: 在此添加命令处理程序代码
	fp = fopen("outfile.txt", "r");
	int duqushu;
	char c;
	CDC* pDC1 = GetDC();
	int a1, a2, a3, a4;
	fscanf(fp, "%d\n", &duqushu);
	if (duqushu < 0)return;
	for (int i = allnum + 1; i <= allnum + duqushu+1;i++) {
		fscanf(fp, "%c\n", &c);
		switch (c) {
		case 'c': {
			My_Circle* circle = new My_Circle;
			Shape* shape1 = circle;
			all[i] = shape1;
			all[i]->pDC = pDC1;
			fscanf(fp, "%d %d %d %d\n", &a1, &a2, &a3, &a4);
			all[i]->point1.x = a1;
			all[i]->point1.y = a2;
			all[i]->point2.x = a3;
			all[i]->point2.y = a4;
			all[i]->draw();
			break;
		}
		case 'l': {
			My_Line* line = new My_Line;
			Shape* shape2 = line;
			all[i] = shape2;
			all[i]->pDC = pDC1;
			fscanf(fp, "%d %d %d %d\n", &a1,&a2,&a3,&a4);
				all[i]->point1.x =a1;
				all[i]->point1.y = a2;
				all[i]->point2.x = a3;
				all[i]->point2.y = a4;
			shape2->draw();
			break;
		}
		case 'r': {
			My_Rectangle* rec = new My_Rectangle;
			Shape* shape3 = rec;
			all[i] = shape3;
			all[i]->pDC = pDC1;
			fscanf(fp, "%d %d %d %d\n", &a1, &a2, &a3, &a4);
			all[i]->point1.x = a1;
			all[i]->point1.y = a2;
			all[i]->point2.x = a3;
			all[i]->point2.y = a4;
			all[i]->draw();
			break;
		}
		case 'p': {
			My_Polygon* poly = new My_Polygon;
			Shape* shape = poly;
			all[i] = shape;
			all[i]->pDC = pDC1;
			fscanf(fp, "%d\n", &shape->flag);
			for (int j = 0; j <= shape->flag-1; j++) {
				fscanf(fp, "%d %d\n", &a1, &a2);
				all[i]->pointnum[j].x = a1;
				all[i]->pointnum[j].y = a2;
			}
			all[i]->draw();
			break;
		}
		}
	}
	allnum = allnum + duqushu+1;
	fclose(fp);
}


void CMFCApplication1View::OnDraw_Polygon()
{
	allnum++;
	// TODO: 在此添加命令处理程序代码
	My_Polygon* polygon = new My_Polygon;
	Shape* shape = polygon;
	shape->flag = 0;
	all[allnum] = shape;
	now = 1;
	
}
void draw_all() {
	
	/*for (int i = 0; i <= allnum; i++) {
		if(all[allnum])
			all[allnum]->draw();
	}*/

}