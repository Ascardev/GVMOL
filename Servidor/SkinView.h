enum SkinType
{
    TYPE_WEAPON,
    TYPE_ARMOR,
    TYPE_SHIELD
}; 

enum SubViewType
{
    TYPE_ARCO,
    TYPE_FOICE,
    TYPE_LANCA,
    TYPE_ESPADA,
    TYPE_GARRA,
    TYPE_PORRETE,
    TYPE_AXE,
    TYPE_ADAGA,
    TYPE_FANTASMA,
    TYPE_CAJADO,
    TYPE_MANOPLA,

    TYPE_ARMOR_B,
    TYPE_ROBE_B
};


class SkinView
{
public:
    virtual						~SkinView();
    static SkinView*				GetInstance() { static SkinView instance; return &instance; };
    BOOL						IsOpen() { return m_Open; }

    void						Init();
    BOOL IsMousePos(int x, int y, int w, int h);
    void						Main();

   

    

    void						Draw();
    void SetSubViewTypeClass();
    void OpenNPC();

    int m_ChangeSkin;

private:
    SkinView();
    void LoadCurrentIMG();
    void GetInfoAndLoadCurrentImg(char * img);
    void ApplySkin();
    BOOL m_Open;
    BOOL						m_bMouseButtonFlag;


    int m_ViewType;
    int m_SubViewType;

    int m_iSDA3DA4;

    int m_MinView;
    int m_MaxView;

    int m_CurrentView;
    int m_LastCurrentView;
    int m_CurrentWidth;
    int m_CurrentHeight;
    char szCurrenFilePath[256];

    int Lx;
    int Rx;

    int ImgX;

    LPDIRECT3DTEXTURE9 CurrentItemDraw;

    LPDIRECT3DTEXTURE9 window;
    LPDIRECT3DTEXTURE9 line;
    LPDIRECT3DTEXTURE9 close;
    LPDIRECT3DTEXTURE9 close_;
    LPDIRECT3DTEXTURE9 L;
    LPDIRECT3DTEXTURE9 L_;
    LPDIRECT3DTEXTURE9 R;
    LPDIRECT3DTEXTURE9 R_;
    LPDIRECT3DTEXTURE9 A;
    LPDIRECT3DTEXTURE9 A_;
    LPDIRECT3DTEXTURE9 d;
    LPDIRECT3DTEXTURE9 d_;
    LPDIRECT3DTEXTURE9 w;
    LPDIRECT3DTEXTURE9 w_;

    LPDIRECT3DTEXTURE9 apply;
    LPDIRECT3DTEXTURE9 apply_;

    LPDIRECT3DTEXTURE9 bow;
    LPDIRECT3DTEXTURE9 axes;
    LPDIRECT3DTEXTURE9 claws;
    LPDIRECT3DTEXTURE9 daggers;
    LPDIRECT3DTEXTURE9 hammers;
    LPDIRECT3DTEXTURE9 javelins;
    LPDIRECT3DTEXTURE9 manopla;
    LPDIRECT3DTEXTURE9 phantoms;
    LPDIRECT3DTEXTURE9 scythes;
    LPDIRECT3DTEXTURE9 swords;
    LPDIRECT3DTEXTURE9 wands;

    LPDIRECT3DTEXTURE9 bow_;
    LPDIRECT3DTEXTURE9 axes_;
    LPDIRECT3DTEXTURE9 claws_;
    LPDIRECT3DTEXTURE9 daggers_;
    LPDIRECT3DTEXTURE9 hammers_;
    LPDIRECT3DTEXTURE9 javelins_;
    LPDIRECT3DTEXTURE9 manopla_;
    LPDIRECT3DTEXTURE9 phantoms_;
    LPDIRECT3DTEXTURE9 scythes_;
    LPDIRECT3DTEXTURE9 swords_;
    LPDIRECT3DTEXTURE9 wands_;

    LPDIRECT3DTEXTURE9 armors;
    LPDIRECT3DTEXTURE9 robes;
    LPDIRECT3DTEXTURE9 shields;

    LPDIRECT3DTEXTURE9 armors_;
    LPDIRECT3DTEXTURE9 robes_;
    LPDIRECT3DTEXTURE9 shields_;

};
