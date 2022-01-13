#pragma once
// Include stdlib
#include <cstdint>
// Include std::map
#include <map>
// Include std::function
#include <functional>

/*
* Cheat's menu.
*/
namespace GUI
{
	/*
	* Show our menu.
	*/
	void Show();

	/*
	* Apply styles for our menu.
	*/
	void Style();

	/*
	* Render our tabs
	*/
	void RenderRagebot();
	void RenderVisuals();
	void RenderMisc();
	void RenderConfig();

	// State of our menu
	inline bool m_bIsOpened = false;
	// Currently active tab
	inline int m_iTab = 0;
}