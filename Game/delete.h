#pragma once

#define INIT( ptr )							{ if( ptr ) { if( !ptr->Init() ) return FALSE; } }
#define INITP( ptr, p )						{ if( ptr ) { if( !ptr->Init( p ) ) return FALSE; } }
#define SHUTDOWN( ptr )						{ if( ptr ) { ptr->Shutdown(); } }

#define RELEASE( ptr )						{ if( ptr ) { ptr->Release(); ptr = NULL; } }

#define DELET( ptr )						{ delete ptr; ptr = NULL; }
#define DELETA( ptr )						{ delete[] ptr; ptr = NULL; }