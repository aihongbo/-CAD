#ifndef sdgm_event_H
#define sdgm_event_H
#include "ncti_base.h"
namespace NCTI
{
	enum class KeyboardCode : Ncti_UInteger
	{
        Nokey = 0,	//!< No key.

		Backspace = 8,	//!< The Backspace key.
		Tab = 9,	//!< The Tab key.
		Clear = 11,	//!< The Clear key.
		Return = 13,	//!< The Return key.
		Shift = 16,	//!< The Shift key.
		Control = 17,	//!< The Control key.
		Alt = 18,	//!< The Alt key.
		Pause = 19,	//!< The Pause key.
		Escape = 27,	//!< The ESC key.

		Space = 32,	//!< The Spacebar key.
		ExclamationMark,			//!< The Exclamation key.
		DoubleQuote,
		Number,
		Dollar,
		Percent,
		Ampersand,
		SingleQuote,
		OpenParen,
		CloseParen,

		Asterisk, 					//!< The Asterisk key.
		Plus, 						//!< The Plus key.
		Comma, 						//!< The Comma key.
		Hyphen, 					//!< The Hyphen key.
		Period,						//!< The Period key.
		Slash, 						//!< The Slash key.

		D0,			 				//!< The 0 (zero) key.
		D1,				 			//!< The 1 (one) key.
		D2, 						//!< The 2 key.
		D3,				 			//!< The 3 key.
		D4, 						//!< The 4 key.
		D5, 						//!< The 5 key.
		D6, 						//!< The 6 key.
		D7, 						//!< The 7 key.
		D8, 						//!< The 8 key.
		D9, 						//!< The 9 key.

		Colon,						//!< The Colon key.
		Semicolon,					//!< The Semicolon key.
		LessThan,
		Equal,						//!< The Equal key.
		GreaterThan,
		QuestionMark,
		AtSymbol,

		A,							//!< The A key.
		B,							//!< The B key.
		C,							//!< The C key.
		D,							//!< The D key.
		E,							//!< The E key.
		F,							//!< The F key.
		G,							//!< The G key.
		H,							//!< The H key.
		I,							//!< The I key.
		J,							//!< The J key.
		K,							//!< The K key.
		L,							//!< The L key.
		M,							//!< The M key.
		N,							//!< The N key.
		O,							//!< The O key.
		P,							//!< The P key.
		Q,							//!< The Q key.
		R,							//!< The R key.
		S,							//!< The S key.
		T,							//!< The T key.
		U,							//!< The U key.
		V,							//!< The V key.
		W,							//!< The W key.
		X,							//!< The X key.
		Y,							//!< The Y key.
		Z,							//!< The Z key.

		OpenBrackets,
		Backslash,
		CloseBrackets,
		Caret,
		Underscore,
		Backtick,

		a,							//!< The lowercase a key.
		b,							//!< The lowercase b key.
		c,							//!< The lowercase c key.
		d,							//!< The lowercase d key.
		e,							//!< The lowercase e key.
		f,							//!< The lowercase f key.
		g,							//!< The lowercase g key.
		h,							//!< The lowercase h key.
		i,							//!< The lowercase i key.
		j,							//!< The lowercase j key.
		k,							//!< The lowercase k key.
		l,							//!< The lowercase l key.
		m,							//!< The lowercase m key.
		n,							//!< The lowercase n key.
		o,							//!< The lowercase o key.
		p,							//!< The lowercase p key.
		q,							//!< The lowercase q key.
		r,							//!< The lowercase r key.
		s,							//!< The lowercase s key.
		t,							//!< The lowercase t key.
		u,							//!< The lowercase u key.
		v,							//!< The lowercase v key.
		w,							//!< The lowercase w key.
		x,							//!< The lowercase x key.
		y,							//!< The lowercase y key.
		z,							//!< The lowercase z key.

		OpenBrace,
		VerticalBar,
		ClosingBrace,
		Tilde,
		Delete,						//!< The Delete key.

		Insert = 1024,				//!< The Insert key.
		Home,						//!< The Home key.
		End,						//!< The End key.
		PageUp,						//!< The Page Up key.
		PageDown,					//!< The Page Down key.

		Help,						//!< The Help key.

		Left,						//!< The Left Arrow key.
		Up,							//!< The Up Arrow key.
		Right,						//!< The Right Arrow key.
		Down,						//!< The Down Arrow key.

		NumPad0, 					//!< The 0 numeric keypad if numlock was off.
		NumPad1, 					//!< The 1 numeric keypad if numlock was off.
		NumPad2, 					//!< The 2 numeric keypad if numlock was off.
		NumPad3, 					//!< The 3 numeric keypad if numlock was off.
		NumPad4, 					//!< The 4 numeric keypad if numlock was off.
		NumPad5, 					//!< The 5 numeric keypad if numlock was off.
		NumPad6, 					//!< The 6 numeric keypad if numlock was off.
		NumPad7, 					//!< The 7 numeric keypad if numlock was off.
		NumPad8, 					//!< The 8 numeric keypad if numlock was off.
		NumPad9, 					//!< The 9 numeric keypad if numlock was off.

		F1,							//!< The F1 key.
		F2,							//!< The F2 key.
		F3,							//!< The F3 key.
		F4,							//!< The F4 key.
		F5,							//!< The F5 key.
		F6,							//!< The F6 key.
		F7,							//!< The F7 key.
		F8,							//!< The F8 key.
		F9,							//!< The F9 key.
		F10,						//!< The F10 key.
		F11,						//!< The F11 key.
		F12,						//!< The F12 key.
		F13,						//!< The F13 key.
		F14,						//!< The F14 key.
		F15,						//!< The F15 key.
		F16,						//!< The F16 key.
		F17,						//!< The F17 key.
		F18,						//!< The F18 key.
		F19,						//!< The F19 key.
		F20,						//!< The F20 key.
		F21,						//!< The F21 key.
		F22,						//!< The F22 key.
		F23,						//!< The F23 key.
		F24,						//!< The F24 key.

		CapsLock,					//!< The Caps Lock key.
		NumLock,					//!< The Num Lock key.
		ScrollLock,					//!< The Scroll Lock key.
		LeftShift,					//!< The left Shift key.
		RightShift,					//!< The right Shift key.
		LeftCtrl,					//!< The left CTRL key.
		RightCtrl,					//!< The right CTRL key.
		LeftAlt,					//!< The left ALT key.
		RightAlt,					//!< The right ALT key.

		Select, 					//!< The Select key.
		Print,						//!< The Print key.
		Execute,		 			//!< The Execute key.
		PrintScreen,	 			//!< The Print Screen key.

		Enter,					//!< The Enter key.
	};

    enum class ActionMode
    {
        e_press,
        e_release,
        e_repeat
    };

	class  MouseButtons
	{
	public:
		MouseButtons() : m_buttons(ncti_button_none) {}
		Ncti_Boolean Equals(MouseButtons const& in_that) const
		{
			return m_buttons == in_that.m_buttons;
		}
		Ncti_Boolean operator== (MouseButtons const& in_that) const
		{
			return Equals(in_that);
		}
		Ncti_Boolean operator!= (MouseButtons const& in_that) const
		{
			return !Equals(in_that);
		}
		Ncti_Boolean None() const { return m_buttons == ncti_button_none; }
		Ncti_Boolean Left() const { return (m_buttons & ncti_button_left) != 0; }
		Ncti_Boolean Right() const { return (m_buttons & ncti_button_right) != 0; }
		Ncti_Boolean Middle() const { return (m_buttons & ncti_button_middle) != 0; }
		Ncti_Boolean X1() const { return (m_buttons & ncti_button_x1) != 0; }
		Ncti_Boolean X2() const { return (m_buttons & ncti_button_x2) != 0; }
		Ncti_Boolean HasAll(MouseButtons const& in_buttons) const { return (m_buttons & in_buttons.m_buttons) == in_buttons.m_buttons; }
		Ncti_Boolean HasAny(MouseButtons const& in_buttons) const { return (m_buttons & in_buttons.m_buttons) != 0; }
		void Left(Ncti_Boolean in_state) { if (in_state) m_buttons |= ncti_button_left; else m_buttons &= ~(ncti_button_left); }
		void Right(Ncti_Boolean in_state) { if (in_state) m_buttons |= ncti_button_right; else m_buttons &= ~(ncti_button_right); }
		void Middle(Ncti_Boolean in_state) { if (in_state) m_buttons |= ncti_button_middle; else m_buttons &= ~(ncti_button_middle); }
		void X1(Ncti_Boolean in_state) { if (in_state) m_buttons |= ncti_button_x1; else m_buttons &= ~(ncti_button_x1); }
		void X2(Ncti_Boolean in_state) { if (in_state) m_buttons |= ncti_button_x2; else m_buttons &= ~(ncti_button_x2); }
		MouseButtons operator+ (MouseButtons const& in_buttons_to_merge)
		{
			MouseButtons ret;
			ret.m_buttons = m_buttons | in_buttons_to_merge.m_buttons;
			return ret;
		}
		MouseButtons operator- (MouseButtons const& in_buttons_to_remove)
		{
			MouseButtons ret;
			ret.m_buttons = m_buttons & ~in_buttons_to_remove.m_buttons;
			return ret;
		}
		MouseButtons& operator+= (MouseButtons const& in_buttons_to_merge) { *this = *this + in_buttons_to_merge; return *this; }
		MouseButtons& operator-= (MouseButtons const& in_buttons_to_remove) { *this = *this - in_buttons_to_remove; return *this; }
		static MouseButtons ButtonLeft() { MouseButtons ret; ret.Left(true); return ret; }
		static MouseButtons ButtonRight() { MouseButtons ret; ret.Right(true); return ret; }
		static MouseButtons ButtonMiddle() { MouseButtons ret; ret.Middle(true); return ret; }
		static MouseButtons ButtonX1() { MouseButtons ret; ret.X1(true); return ret; }
		static MouseButtons ButtonX2() { MouseButtons ret; ret.X2(true); return ret; }
	protected:
		enum Buttons
		{
			ncti_button_none = 0x0000,
			ncti_button_left = 0x0001,
			ncti_button_right = 0x0002,
			ncti_button_middle = 0x0004,
			ncti_button_x1 = 0x0008,
			ncti_button_x2 = 0x0010
		};
		Ncti_Integer m_buttons;
	};
	
    class  ModifierKeys
	{
	public:
		ModifierKeys() : m_modifiers(ncti_key_none) {}
		Ncti_Boolean Equals(ModifierKeys const& in_that) const
		{
			return m_modifiers == in_that.m_modifiers;
		}
		Ncti_Boolean operator== (ModifierKeys const& in_that) const
		{
			return Equals(in_that);
		}
		Ncti_Boolean operator!= (ModifierKeys const& in_that) const
		{
			return !Equals(in_that);
		}
		Ncti_Boolean None() const { return m_modifiers == ncti_key_none; }
		Ncti_Boolean Shift() const { return (m_modifiers & ncti_key_shift) != 0; }
		Ncti_Boolean Control() const { return (m_modifiers & ncti_key_control) != 0; }
		Ncti_Boolean Alt() const { return (m_modifiers & ncti_key_alt) != 0; }
		Ncti_Boolean Meta() const { return (m_modifiers & ncti_key_meta) != 0; }
		Ncti_Boolean CapsLock() const { return (m_modifiers & ncti_key_caps_lock) != 0; }
		Ncti_Boolean NumLock() const { return (m_modifiers & ncti_key_num_lock) != 0; }
		Ncti_Boolean ScrollLock() const { return (m_modifiers & ncti_key_scroll_lock) != 0; }
		Ncti_Boolean RightShift() const { return (m_modifiers & ncti_key_right_shift) != 0; }
		Ncti_Boolean LeftShift() const { return (m_modifiers & ncti_key_left_shift) != 0; }
		Ncti_Boolean RightControl() const { return (m_modifiers & ncti_key_right_control) != 0; }
		Ncti_Boolean LeftControl() const { return (m_modifiers & ncti_key_left_control) != 0; }
		Ncti_Boolean RightAlt() const { return (m_modifiers & ncti_key_right_alt) != 0; }
		Ncti_Boolean LeftAlt() const { return (m_modifiers & ncti_key_left_alt) != 0; }
		Ncti_Boolean RightMeta() const { return (m_modifiers & ncti_key_right_meta) != 0; }
		Ncti_Boolean LeftMeta() const { return (m_modifiers & ncti_key_left_meta) != 0; }
		Ncti_Boolean HasAll(ModifierKeys const& in_keys) const { return (m_modifiers & in_keys.m_modifiers) == in_keys.m_modifiers; }
		Ncti_Boolean HasAny(ModifierKeys const& in_keys) const { return (m_modifiers & in_keys.m_modifiers) != 0; }
		void Shift(Ncti_Boolean in_state) { if (in_state) m_modifiers |= ncti_key_shift; else m_modifiers &= ~(ncti_key_shift); }
		void Control(Ncti_Boolean in_state) { if (in_state) m_modifiers |= ncti_key_control; else m_modifiers &= ~(ncti_key_control); }
		void Alt(Ncti_Boolean in_state) { if (in_state) m_modifiers |= ncti_key_alt; else m_modifiers &= ~(ncti_key_alt); }
		void Meta(Ncti_Boolean in_state) { if (in_state) m_modifiers |= ncti_key_meta; else m_modifiers &= ~(ncti_key_meta); }
		void CapsLock(Ncti_Boolean in_state) { if (in_state) m_modifiers |= ncti_key_caps_lock; else m_modifiers &= ~(ncti_key_caps_lock); }
		void NumLock(Ncti_Boolean in_state) { if (in_state) m_modifiers |= ncti_key_num_lock; else m_modifiers &= ~(ncti_key_num_lock); }
		void ScrollLock(Ncti_Boolean in_state) { if (in_state) m_modifiers |= ncti_key_scroll_lock; else m_modifiers &= ~(ncti_key_scroll_lock); }
		void RightShift(Ncti_Boolean in_state) { if (in_state) m_modifiers |= ncti_key_right_shift; else m_modifiers &= ~(ncti_key_right_shift); }
		void LeftShift(Ncti_Boolean in_state) { if (in_state) m_modifiers |= ncti_key_left_shift; else m_modifiers &= ~(ncti_key_left_shift); }
		void RightControl(Ncti_Boolean in_state) { if (in_state) m_modifiers |= ncti_key_right_control; else m_modifiers &= ~(ncti_key_right_control); }
		void LeftControl(Ncti_Boolean in_state) { if (in_state) m_modifiers |= ncti_key_left_control; else m_modifiers &= ~(ncti_key_left_control); }
		void RightAlt(Ncti_Boolean in_state) { if (in_state) m_modifiers |= ncti_key_right_alt; else m_modifiers &= ~(ncti_key_right_alt); }
		void LeftAlt(Ncti_Boolean in_state) { if (in_state) m_modifiers |= ncti_key_left_alt; else m_modifiers &= ~(ncti_key_left_alt); }
		void RightMeta(Ncti_Boolean in_state) { if (in_state) m_modifiers |= ncti_key_right_meta; else m_modifiers &= ~(ncti_key_right_meta); }
		void LeftMeta(Ncti_Boolean in_state) { if (in_state) m_modifiers |= ncti_key_left_meta; else m_modifiers &= ~(ncti_key_left_meta); }
		ModifierKeys operator+ (ModifierKeys const& in_modifiers_to_merge)
		{
			ModifierKeys ret;
			ret.m_modifiers = m_modifiers | in_modifiers_to_merge.m_modifiers;
			return ret;
		}
		ModifierKeys operator- (ModifierKeys const& in_modifiers_to_remove)
		{
			ModifierKeys ret;
			ret.m_modifiers = m_modifiers & ~in_modifiers_to_remove.m_modifiers;
			return ret;
		}
		ModifierKeys& operator+= (ModifierKeys const& in_modifiers_to_merge) { *this = *this + in_modifiers_to_merge; return *this; }
		ModifierKeys& operator-= (ModifierKeys const& in_modifiers_to_remove) { *this = *this - in_modifiers_to_remove; return *this; }
		static ModifierKeys KeyShift() { ModifierKeys ret; ret.Shift(true); return ret; }
		static ModifierKeys KeyControl() { ModifierKeys ret; ret.Control(true); return ret; }
		static ModifierKeys KeyAlt() { ModifierKeys ret; ret.Alt(true); return ret; }
		static ModifierKeys KeyMeta() { ModifierKeys ret; ret.Meta(true); return ret; }
		static ModifierKeys KeyCapsLock() { ModifierKeys ret; ret.CapsLock(true); return ret; }
		static ModifierKeys KeyNumLock() { ModifierKeys ret; ret.NumLock(true); return ret; }
		static ModifierKeys KeyScrollLock() { ModifierKeys ret; ret.ScrollLock(true); return ret; }
		static ModifierKeys KeyRightShift() { ModifierKeys ret; ret.RightShift(true); return ret; }
		static ModifierKeys KeyLeftShift() { ModifierKeys ret; ret.LeftShift(true); return ret; }
		static ModifierKeys KeyRightControl() { ModifierKeys ret; ret.RightControl(true); return ret; }
		static ModifierKeys KeyLeftControl() { ModifierKeys ret; ret.LeftControl(true); return ret; }
		static ModifierKeys KeyRightAlt() { ModifierKeys ret; ret.RightAlt(true); return ret; }
		static ModifierKeys KeyLeftAlt() { ModifierKeys ret; ret.LeftAlt(true); return ret; }
		static ModifierKeys KeyRightMeta() { ModifierKeys ret; ret.RightMeta(true); return ret; }
		static ModifierKeys KeyLeftMeta() { ModifierKeys ret; ret.LeftMeta(true); return ret; }
	protected:
		enum Modifiers
		{
			ncti_key_none = 0x0000,
			ncti_key_caps_lock = 0x0001,
			ncti_key_num_lock = 0x0002,
			ncti_key_scroll_lock = 0x0004,
			ncti_key_right_shift = 0x0008,
			ncti_key_left_shift = 0x0010,
			ncti_key_right_control = 0x0020,
			ncti_key_left_control = 0x0040,
			ncti_key_right_alt = 0x0080,
			ncti_key_left_alt = 0x0100,
			ncti_key_right_meta = 0x0200,
			ncti_key_left_meta = 0x0400,
			ncti_key_shift = ncti_key_left_shift | ncti_key_right_shift,
			ncti_key_control = ncti_key_left_control | ncti_key_right_control,
			ncti_key_alt = ncti_key_left_alt | ncti_key_right_alt,
			ncti_key_meta = ncti_key_left_meta | ncti_key_right_meta,
		};
		Ncti_Integer m_modifiers;
	};
}
#endif
