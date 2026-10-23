#pragma once

// Reconstructed TLBB engine interface from the existing CGameInterface
// declarations in this repository. This header contains declarations only.
#include "TDNode.h"
#include "TDMath.h"
#include "../../Shared/Common/GameDefine2.h"

class tActionItem;
class tObject_Item;
class CObject;

#ifndef GUID_t
typedef UINT GUID_t;
#endif

class tGameInterfaceBase : public tNode {
public:
    virtual VOID Object_SelectAsMainTarget(INT idObj, int iType = 0) = 0;
    virtual VOID Object_ShowContexMenu(INT idObj, BOOL showMyself = FALSE) = 0;

    virtual VOID Player_MoveTo(const fVector2& fvAimPos) = 0;
    virtual VOID Player_AUTOHit(const int autoHit) = 0;
    virtual VOID Player_UseSkill(INT idSkill) = 0;
    virtual VOID Player_UseSkill(INT idSkill, INT idObj) = 0;
    virtual VOID Player_UseSkill(INT idSkill, const fVector2& fvPos) = 0;
    virtual VOID Player_UseSkill(INT idSkill, FLOAT fDir) = 0;
    virtual VOID Player_UseSkill(INT idSkill, const GUID_t& guid) = 0;
    virtual VOID Player_UseLifeAbility(INT idPrescription, INT nMakeCount) = 0;
    virtual VOID Player_UseLifeAbility(INT idPrescription) = 0;
    virtual VOID Player_DestroyEquip(const tObject_Item* pEquip) = 0;
    virtual VOID Player_UnEquip(const tObject_Item* pEquip) = 0;
    virtual VOID Player_AskLevelUp(VOID) = 0;
    virtual VOID Player_AskCleanBat1Point(VOID) = 0;
    virtual VOID Player_Speak(INT idObj) = 0;

    virtual VOID TripperObj_Active(UINT nId) = 0;
    virtual VOID ItemBox_PickItem(tObject_Item* pItem) = 0;

    virtual VOID PacketItem_UserItem(tActionItem* pActionItem, int targetServerID, fVector2& fvPos) = 0;
    virtual VOID PacketItem_UserItem_ToTarget(INT nIndex, UINT nTargetID) = 0;
    virtual VOID PacketItem_UserEquip(INT nIndex) = 0;
    virtual VOID PacketItem_UserGem(INT nGemIndex, INT equipIndex) = 0;
    virtual VOID PacketItem_Destroy(INT nIndex) = 0;

    virtual VOID GM_SendCommand(LPCSTR strCommand) = 0;
    virtual VOID SendChatCommand(INT nChannelID, INT nChatType, INT nTeamID,
                                 LPCTSTR context, LPCTSTR targetName) = 0;

    virtual VOID Scene_SetPostFilter(LPCTSTR filterName) = 0;
    virtual VOID Scene_SetLightmapQuality(INT nQuality) = 0;

    virtual VOID Skill_SetActive(tActionItem* pActiveSkill) = 0;
    virtual tActionItem* Skill_GetActive(VOID) = 0;
    virtual VOID Skill_CancelAction(VOID) = 0;

    virtual VOID Booth_BuyItem(tObject_Item* pItem) = 0;
    virtual VOID Booth_SellItem(tObject_Item* pItem) = 0;
    virtual VOID Booth_Close(VOID) = 0;
    virtual VOID Booth_Repair(BOOL bAll, INT bagIndex, BOOL isInBag = TRUE) = 0;
    virtual VOID Booth_EnterRepair(VOID) = 0;

    virtual VOID Title_UpdateCurTitle(BYTE titleType, SHORT titleData) = 0;
    virtual VOID Stall_OpenStallSale(INT nObjId) = 0;
    virtual ENUM_RELATION GetCampType(CObject* pObjA, CObject* pObjB) = 0;

protected:
    WX_DECLARE_DYNAMIC(tGameInterfaceBase);
};
