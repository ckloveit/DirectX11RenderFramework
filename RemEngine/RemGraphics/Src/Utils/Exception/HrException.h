#pragma once
#include "RemWin.h"
#include "BaseException.h"

class HrException : public BaseException
{
public:
	HrException(int line, const char* file, HRESULT hr) noexcept;
	const char* what() const noexcept override;
	const char* GetType() const noexcept override;
	HRESULT GetErrorCode() const noexcept;
	std::string GetErrorDescription() const noexcept;
private:
	HRESULT hr;
};