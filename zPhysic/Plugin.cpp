// This file added in headers queue
// File: "Sources.h"
#include "resource.h"
#include <chrono>

namespace GOTHIC_ENGINE {

  void Game_Entry() {
  }
  
  void Game_Init() {
  }

  void Game_Exit() {
  }

  void Game_PreLoop() {
  }

  void Game_Loop() {
    zPhysicalVobProvider::UpdateAllProvider();
    PhysicalWorld->DoPhysic( ztimer->frameTimeFloat );
    screen->Print( 400, 800, Z "Frame time: " + Z string( ztimer->frameTimeFloat ) );

    // DELETE ME
    if( zKeyToggled( KEY_U ) ) {
      zVEC3 camPos = ogame->GetCameraVob()->GetPositionWorld();
      zVEC3 camVec = ogame->GetCameraVob()->GetAtVectorWorld() * 50.0f;
      zPhysicalSphere* sphere = zPhysicalSphere::CreateSphere( 30.0f, camPos, 20.0, true );
      zCVob* vob = new zCVob();
      vob->SetVisual( "BALL.3DS" );
      ogame->GetGameWorld()->AddVob( vob );
      zPhysicalVobProvider* vobConnector = new zPhysicalVobProvider( sphere, vob );
      sphere->Release();
      vobConnector->SetVelocity( camVec );
      PhysicalWorld->AddObject( vobConnector->GetPhysicalMesh() );
    }

    if( zKeyToggled( KEY_I ) ) {
      zMAT4 camTrafo = ogame->GetCameraVob()->trafoObjToWorld;
      zVEC3 camVec = ogame->GetCameraVob()->GetAtVectorWorld() * 50.0f;
      zPhysicalBox* sphere = zPhysicalBox::CreateBox( zVEC3( 60.0f, 35.0f, 40.0f ), camTrafo, 150.0, true );
      zCVob* vob = new zCVob();
      vob->SetVisual( "BOX2.3DS" );
      ogame->GetGameWorld()->AddVob( vob );
      zPhysicalVobProvider* vobConnector = new zPhysicalVobProvider( sphere, vob );
      sphere->Release();
      vobConnector->SetVelocity( camVec );
      PhysicalWorld->AddObject( vobConnector->GetPhysicalMesh() );
    }

    if( zKeyToggled( KEY_O ) ) {
      zVEC3 camPos = ogame->GetCameraVob()->GetPositionWorld();
      zVEC3 camVec = ogame->GetCameraVob()->GetAtVectorWorld() * 90.0f;
      zPhysicalTriangleMesh* sphere = zPhysicalTriangleMesh::CreatePolyMesh( "ADDON_STONES_CRYSTAL_01_228P.3DS", camPos, 500.0, true );

      if( sphere ) {
        zCVob* vob = new zCVob();
        vob->SetVisual( "ADDON_STONES_CRYSTAL_01_228P.3DS" );
        ogame->GetGameWorld()->AddVob( vob );
        zPhysicalVobProvider* vobConnector = new zPhysicalVobProvider( sphere, vob );
        sphere->Release();
        vobConnector->SetVelocity( camVec );
        PhysicalWorld->AddObject( vobConnector->GetPhysicalMesh() );
      }
      else
        Message::Box( "Can not load mesh" );
    }



    if( zKeyToggled( KEY_P ) ) {
      zVEC3 camPos = ogame->GetCameraVob()->GetPositionWorld();
      zVEC3 camVec = ogame->GetCameraVob()->GetAtVectorWorld() * 90.0f;
      zPhysicalHullMesh* sphere = zPhysicalHullMesh::CreatePolyMesh( "ADDON_LSTTEMP_STONEGUARDIAN_LARGE_01.3DS", camPos, 1500.0, true );

      if( sphere ) {
        zCVob* vob = new zCVob();
        vob->SetVisual( "ADDON_LSTTEMP_STONEGUARDIAN_LARGE_01.3DS" );
        ogame->GetGameWorld()->AddVob( vob );
        zPhysicalVobProvider* vobConnector = new zPhysicalVobProvider( sphere, vob );
        sphere->Release();
        vobConnector->SetVelocity( camVec );
        PhysicalWorld->AddObject( vobConnector->GetPhysicalMesh() );
      }
      else
        Message::Box( "Can not load mesh" );
    }
  }

  void Game_PostLoop() {
  }

  void Game_MenuLoop() {
  }

  // Information about current saving or loading world
  TSaveLoadGameInfo& SaveLoadGameInfo = UnionCore::SaveLoadGameInfo;

  void Game_SaveBegin() {
  }

  void Game_SaveEnd() {
  }

  void LoadBegin() {
    zPhysicalVobProvider::DeleteAllProvider();
  }

  void LoadEnd() {
    PhysicalWorld = new zPhysicalWorld();
    PhysicalWorld->InitializeWorldMesh();
    for( uint i = 0; i < PhysicalMeshQueue.GetNum(); i++ ) {
      zPhysicalMesh* mesh = PhysicalMeshQueue[i];
      PhysicalWorld->AddObject( mesh );
      mesh->Release();
    }

    PhysicalMeshQueue.Clear();
  }

  void Game_LoadBegin_NewGame() {
    LoadBegin();
  }

  void Game_LoadEnd_NewGame() {
    LoadEnd();
  }

  void Game_LoadBegin_SaveGame() {
    LoadBegin();
  }

  void Game_LoadEnd_SaveGame() {
    LoadEnd();
  }

  void Game_LoadBegin_ChangeLevel() {
    LoadBegin();
  }

  void Game_LoadEnd_ChangeLevel() {
    LoadEnd();
  }

  void Game_LoadBegin_Trigger() {
  }
  
  void Game_LoadEnd_Trigger() {
  }
  
  void Game_Pause() {
  }
  
  void Game_Unpause() {
  }
  
  void Game_DefineExternals() {
  }

  void Game_ApplyOptions() {
  }

  /*
  Functions call order on Game initialization:
    - Game_Entry           * Gothic entry point
    - Game_DefineExternals * Define external script functions
    - Game_Init            * After DAT files init
  
  Functions call order on Change level:
    - Game_LoadBegin_Trigger     * Entry in trigger
    - Game_LoadEnd_Trigger       *
    - Game_Loop                  * Frame call window
    - Game_LoadBegin_ChangeLevel * Load begin
    - Game_SaveBegin             * Save previous level information
    - Game_SaveEnd               *
    - Game_LoadEnd_ChangeLevel   *
  
  Functions call order on Save game:
    - Game_Pause     * Open menu
    - Game_Unpause   * Click on save
    - Game_Loop      * Frame call window
    - Game_SaveBegin * Save begin
    - Game_SaveEnd   *
  
  Functions call order on Load game:
    - Game_Pause              * Open menu
    - Game_Unpause            * Click on load
    - Game_LoadBegin_SaveGame * Load begin
    - Game_LoadEnd_SaveGame   *
  */

#define AppDefault True
  CApplication* lpApplication = !CHECK_THIS_ENGINE ? Null : CApplication::CreateRefApplication(
    Enabled( AppDefault ) Game_Entry,
    Enabled( AppDefault ) Game_Init,
    Enabled( AppDefault ) Game_Exit,
    Enabled( AppDefault ) Game_PreLoop,
    Enabled( AppDefault ) Game_Loop,
    Enabled( AppDefault ) Game_PostLoop,
    Enabled( AppDefault ) Game_MenuLoop,
    Enabled( AppDefault ) Game_SaveBegin,
    Enabled( AppDefault ) Game_SaveEnd,
    Enabled( AppDefault ) Game_LoadBegin_NewGame,
    Enabled( AppDefault ) Game_LoadEnd_NewGame,
    Enabled( AppDefault ) Game_LoadBegin_SaveGame,
    Enabled( AppDefault ) Game_LoadEnd_SaveGame,
    Enabled( AppDefault ) Game_LoadBegin_ChangeLevel,
    Enabled( AppDefault ) Game_LoadEnd_ChangeLevel,
    Enabled( AppDefault ) Game_LoadBegin_Trigger,
    Enabled( AppDefault ) Game_LoadEnd_Trigger,
    Enabled( AppDefault ) Game_Pause,
    Enabled( AppDefault ) Game_Unpause,
    Enabled( AppDefault ) Game_DefineExternals,
    Enabled( AppDefault ) Game_ApplyOptions
  );
}