class g_DeviceFont
{
public:
	IDirect3D9* Direct3D;
	IDirect3DDevice9* Device9;
	D3DPRESENT_PARAMETERS d3dpp ;

	ID3DXSprite* Sprite;       
	ID3DXFont* Fonts;
	ID3DXFont* FontsItem;
	D3DXFONT_DESC fdesc;
	D3DXFONT_DESC fdescItem;

public:
	g_DeviceFont(void);
	~g_DeviceFont(void);

	bool Create(HWND g_hWnd);
	bool DrawString(const char* msg, int x, int y, D3DCOLOR color = D3DCOLOR_ARGB(255, 255, 255, 255));
	bool DrawStringItem(const char* msg , int x , int y , D3DCOLOR color = D3DCOLOR_ARGB( 255,0,0,0) );

};

extern g_DeviceFont dv_font;