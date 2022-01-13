#pragma once
// Include CALL_VIRTUAL, stdlib, IAppSystem
#include "../platform.h"
// Include CVector4
#include "../types/vector.h"
// Include CUserCmd, CVerifiedUserCmd
#include "prediction.h"

#define MULTIPLAYER_BACKUP			150

struct InputEvent_t;
class CBaseCombatWeapon;

namespace U
{
	/*
	* Just a pointer handle.
	*/
	using HInputContextHandle = std::uintptr_t*;
	using HInputCursorHandle = std::uintptr_t*;
}

enum { INPUT_CONTEXT_HANDLE_INVALID = 0x0, };

class IInputStackSystem : public IAppSystem
{
public:
	virtual U::HInputContextHandle PushInputContext() = 0;
	virtual void		PopInputContext() = 0;
	virtual void		EnableInputContext(U::HInputContextHandle Context, bool Enable) = 0;
	virtual void		SetCursorVisible(U::HInputContextHandle Context, bool Visible) = 0;
	virtual void		SetCursorIcon(U::HInputContextHandle Context, U::HInputCursorHandle Cursor) = 0;
	virtual void		SetMouseCapture(U::HInputContextHandle Context, bool Enable) = 0;
	virtual void		SetCursorPosition(U::HInputContextHandle Context, int X, int Y) = 0;
	virtual bool		IsTopmostEnabledContext(U::HInputContextHandle Context) const = 0;
};

enum EButtonCode
{
	BUTTON_CODE_INVALID = -1,
	BUTTON_CODE_NONE = 0,
	KEY_FIRST = 0,
	KEY_NONE = 0,
	KEY_0,
	KEY_1,
	KEY_2,
	KEY_3,
	KEY_4,
	KEY_5,
	KEY_6,
	KEY_7,
	KEY_8,
	KEY_9,
	KEY_A,
	KEY_B,
	KEY_C,
	KEY_D,
	KEY_E,
	KEY_F,
	KEY_G,
	KEY_H,
	KEY_I,
	KEY_J,
	KEY_K,
	KEY_L,
	KEY_M,
	KEY_N,
	KEY_O,
	KEY_P,
	KEY_Q,
	KEY_R,
	KEY_S,
	KEY_T,
	KEY_U,
	KEY_V,
	KEY_W,
	KEY_X,
	KEY_Y,
	KEY_Z,
	KEY_PAD_0,
	KEY_PAD_1,
	KEY_PAD_2,
	KEY_PAD_3,
	KEY_PAD_4,
	KEY_PAD_5,
	KEY_PAD_6,
	KEY_PAD_7,
	KEY_PAD_8,
	KEY_PAD_9,
	KEY_PAD_DIVIDE,
	KEY_PAD_MULTIPLY,
	KEY_PAD_MINUS,
	KEY_PAD_PLUS,
	KEY_PAD_ENTER,
	KEY_PAD_DECIMAL,
	KEY_LBRACKET,
	KEY_RBRACKET,
	KEY_SEMICOLON,
	KEY_APOSTROPHE,
	KEY_BACKQUOTE,
	KEY_COMMA,
	KEY_PERIOD,
	KEY_SLASH,
	KEY_BACKSLASH,
	KEY_MINUS,
	KEY_EQUAL,
	KEY_ENTER,
	KEY_SPACE,
	KEY_BACKSPACE,
	KEY_TAB,
	KEY_CAPSLOCK,
	KEY_NUMLOCK,
	KEY_ESCAPE,
	KEY_SCROLLLOCK,
	KEY_INSERT,
	KEY_DELETE,
	KEY_HOME,
	KEY_END,
	KEY_PAGEUP,
	KEY_PAGEDOWN,
	KEY_BREAK,
	KEY_LSHIFT,
	KEY_RSHIFT,
	KEY_LALT,
	KEY_RALT,
	KEY_LCONTROL,
	KEY_RCONTROL,
	KEY_LWIN,
	KEY_RWIN,
	KEY_APP,
	KEY_UP,
	KEY_LEFT,
	KEY_DOWN,
	KEY_RIGHT,
	KEY_F1,
	KEY_F2,
	KEY_F3,
	KEY_F4,
	KEY_F5,
	KEY_F6,
	KEY_F7,
	KEY_F8,
	KEY_F9,
	KEY_F10,
	KEY_F11,
	KEY_F12,
	KEY_CAPSLOCKTOGGLE,
	KEY_NUMLOCKTOGGLE,
	KEY_SCROLLLOCKTOGGLE,
	KEY_LAST = 106,
	KEY_COUNT = 107,
	MOUSE_FIRST = 107,
	MOUSE_LEFT = 107,
	MOUSE_RIGHT,
	MOUSE_MIDDLE,
	MOUSE_4,
	MOUSE_5,
	MOUSE_WHEEL_UP,
	MOUSE_WHEEL_DOWN,
};

enum EAnalogCode
{
	ANALOG_CODE_INVALID = -1,
	MOUSE_X = 0,
	MOUSE_Y,
	MOUSE_XY,
	MOUSE_WHEEL,
};

enum { INVALID_USER_ID = -1, };

class IInputSystem : public IAppSystem
{
public:
	virtual void AttachToWindow(void* hWnd) = 0;
	virtual void DetachFromWindow() = 0;
	virtual void EnableInput(bool bEnable) = 0;
	virtual void EnableMessagePump(bool bEnable) = 0;
	virtual void PollInputState(bool bIsInGame = false) = 0;
	virtual int GetPollTick() const = 0;
	virtual bool IsButtonDown(EButtonCode code) const = 0;
	virtual int GetButtonPressedTick(EButtonCode code) const = 0;
	virtual int GetButtonReleasedTick(EButtonCode code) const = 0;
	virtual int GetAnalogValue(EAnalogCode code) const = 0;
	virtual int GetAnalogDelta(EAnalogCode code) const = 0;
	virtual int GetEventCount() const = 0;
	virtual const void* GetEventData() const = 0;
	virtual bool	   MotionControllerActive() const = 0;
	virtual CVector4 GetMotionControllerOrientation() const = 0;
	virtual float	   GetMotionControllerPosX() const = 0;
	virtual float	   GetMotionControllerPosY() const = 0;
	virtual int		   GetMotionControllerDeviceStatus() const = 0;
	virtual std::uint64_t		   GetMotionControllerDeviceStatusFlags() const = 0;
	virtual void	   SetMotionControllerDeviceStatus(int nStatus) = 0;
	virtual void	   SetMotionControllerCalibrationInvalid() = 0;
	virtual void	   StepMotionControllerCalibration() = 0;
	virtual void	   ResetMotionControllerScreenCalibration() = 0;
	virtual void PostUserEvent(const InputEvent_t& event) = 0;
	virtual int GetJoystickCount() const = 0;
	virtual void EnableJoystickInput(int nJoystick, bool bEnable) = 0;
	virtual void EnableJoystickDiagonalPOV(int nJoystick, bool bEnable) = 0;
	virtual void SampleDevices() = 0;
	virtual void SetRumble(float fLeftMotor, float fRightMotor, int userId = INVALID_USER_ID) = 0;
	virtual void StopRumble(int userId = INVALID_USER_ID) = 0;
	virtual void ResetInputState() = 0;
	virtual const char* ButtonCodeToString(EButtonCode code) const = 0;
	virtual const char* AnalogCodeToString(EAnalogCode code) const = 0;
	virtual EButtonCode StringToButtonCode(const char* pString) const = 0;
	virtual EAnalogCode StringToAnalogCode(const char* pString) const = 0;
	virtual void SleepUntilInput(int nMaxSleepTimeMS = -1) = 0;
	virtual EButtonCode VirtualKeyToButtonCode(int nVirtualKey) const = 0;
	virtual int ButtonCodeToVirtualKey(EButtonCode code) const = 0;
	virtual EButtonCode ScanCodeToButtonCode(int lParam) const = 0;
	virtual int GetPollCount() const = 0;
	virtual void SetCursorPosition(int x, int y) = 0;
};

class CInput
{
public:
	CALL_VIRTUAL(9U,	SelectWeapon(CBaseCombatWeapon* Weapon),	void(__thiscall*)(void*, CBaseCombatWeapon*), Weapon);

	FORCEINLINE CUserCmd*			GetUserCmd(int Seq) { return &m_pCommands[Seq % MULTIPLAYER_BACKUP]; }
	FORCEINLINE CVerifiedUserCmd*	GetVerifiedUserCmd(int Seq) { return &m_pVerifiedCommands[Seq % MULTIPLAYER_BACKUP]; }

public:
	pad_t			_0[12];
	bool			m_bTrackIRAvailable;
	bool			m_bMouseInitialized;
	bool			m_bMouseActive;
	pad_t			_1[4];
	float			m_flAccumulatedMove;
	float			m_flLastAutoAimValue;
	pad_t			_2[166];
	bool			m_bCamInThirdPerson;
	pad_t			_3[2];
	CVector3		m_vecCamOffset;
	pad_t			_4[52];
	int				m_nClearInputState;
	CUserCmd*		m_pCommands;
	CVerifiedUserCmd* m_pVerifiedCommands;
};