// �� MFC ���� �ҽ� �ڵ�� MFC Microsoft Office Fluent ����� �������̽�("Fluent UI")�� 
// ����ϴ� ����� ���� �ָ�, MFC C++ ���̺귯�� ����Ʈ��� ���Ե� 
// Microsoft Foundation Classes Reference �� ���� ���� ������ ���� 
// �߰������� �����Ǵ� �����Դϴ�.  
// Fluent UI�� ����, ��� �Ǵ� �����ϴ� �� ���� ��� ����� ������ �����˴ϴ�.  
// Fluent UI ���̼��� ���α׷��� ���� �ڼ��� ������ 
// http://go.microsoft.com/fwlink/?LinkId=238214.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// GDAL_S57View.cpp : CGDAL_S57View Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "GDAL_S57.h"
#endif

#include "GDAL_S57Doc.h"
#include "GDAL_S57View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "ogr_api.h"
#include "ogrsf_frmts.h"

// CGDAL_S57View

IMPLEMENT_DYNCREATE(CGDAL_S57View, CView)

BEGIN_MESSAGE_MAP(CGDAL_S57View, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CGDAL_S57View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_SETCURSOR()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// CGDAL_S57View ����/�Ҹ�

CGDAL_S57View::CGDAL_S57View()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	_putenv("RETURN_LINKAGES=ON,RETURN_PRIMITIVES=ON");
	CPLSetConfigOption("OGR_S57_OPTIONS", "RETURN_LINKAGES=ON,RETURN_PRIMITIVES=ON");

	OGRRegisterAll();
	
	CString encFilePathName("..\\KR4G1E30.000");
	OGRDataSource* pDS =  OGRSFDriverRegistrar::Open(_bstr_t(encFilePathName));
	
	int cnt = pDS->GetLayerCount();
	
	for (int i = 0; i < cnt; i++)
	{
		OGRLayer* layer = pDS->GetLayer(i);
		

		CString strLayerName;
		strLayerName = layer->GetName();

		if (strLayerName.Compare(_T("M_QUAL"))) continue;
		OutputDebugString(_bstr_t(layer->GetName()) + _T("\n"));
		OGRFeatureDefn* fDefn = layer->GetLayerDefn();

		layer->ResetReading();
		layer->GetFeatureCount();
		

		OGRFeature* fe = nullptr;
		while (fe = (layer->GetNextFeature()))
		{
			int fcnt = fe->GetFieldCount();
				
			for (int j = 0; j < fcnt; j++)
			{
				OGRFieldDefn* fd = fe->GetFieldDefnRef(j);
				OutputDebugString(_bstr_t(fd->GetNameRef()) + _T("\n"));
			}

			OGRGeometry* geo = fe->GetGeometryRef();
			OGRLineString* line = (OGRLineString*)geo;



		
		}
		
	}
	OGRDataSource::DestroyDataSource(pDS);

	m_bLMove = false;
}

CGDAL_S57View::~CGDAL_S57View()
{
	OGRCleanupAll();;
}

BOOL CGDAL_S57View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CGDAL_S57View �׸���

void CGDAL_S57View::OnDraw(CDC* pDC)
{
	CGDAL_S57Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
	pDC->Ellipse(m_ptCurrent.x - 5, m_ptCurrent.y - 5, m_ptCurrent.x + 5, m_ptCurrent.y + 5);
}


// CGDAL_S57View �μ�


void CGDAL_S57View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CGDAL_S57View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CGDAL_S57View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CGDAL_S57View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}

void CGDAL_S57View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CGDAL_S57View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CGDAL_S57View ����

#ifdef _DEBUG
void CGDAL_S57View::AssertValid() const
{
	CView::AssertValid();
}

void CGDAL_S57View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGDAL_S57Doc* CGDAL_S57View::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGDAL_S57Doc)));
	return (CGDAL_S57Doc*)m_pDocument;
}
#endif //_DEBUG


// CGDAL_S57View �޽��� ó����


void CGDAL_S57View::OnMouseMove(UINT nFlags, CPoint point)
{
	m_ptCurrent = point;

	if (nFlags & MK_LBUTTON)
	{
		m_bLMove = true;
		SetCursor(AfxGetApp()->LoadStandardCursor(IDC_WAIT));
	}
	else
	{
		m_bLMove = false;
	}

	Invalidate(FALSE);

	CView::OnMouseMove(nFlags, point);
}


BOOL CGDAL_S57View::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if (m_bLMove)
	{
		OutputDebugString(_T("A\n"));
	}

	return CView::OnSetCursor(pWnd, nHitTest, message);
}


void CGDAL_S57View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	SetCapture();
	CView::OnLButtonDown(nFlags, point);
}


void CGDAL_S57View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	ReleaseCapture();
	CView::OnLButtonUp(nFlags, point);
}
