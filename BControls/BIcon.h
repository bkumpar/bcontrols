#pragma once

class BIcon
{
	friend class BIconList;
	friend class BNotificationIcon;
public:
    BIcon();
    BIcon(HICON hIcon);
    BIcon(std::wstring fileName);
    BIcon(int resourceId);
    ~BIcon();
    HICON hIcon();
private:
    HICON _hIcon;
};
