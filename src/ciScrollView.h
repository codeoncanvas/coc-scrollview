//
//	    ┌─┐╔═╗┌┬┐┌─┐
//      │  ║ ║ ││├┤
//      └─┘╚═╝─┴┘└─┘
//	 ┌─┐┌─┐╔╗╔┬  ┬┌─┐┌─┐
//	 │  ├─┤║║║└┐┌┘├─┤└─┐
//	 └─┘┴ ┴╝╚╝ └┘ ┴ ┴└─┘
//	http://codeoncanvas.cc
//
// Created by Rene Christen on 28/01/2016.
// Copyright (c) 2016, Code on Canvas Pty Ltd
//

#pragma once

#ifdef COC_CI

#include "cocScrollView.h"
#include "ciButton.h"

namespace coc {

class ciScrollView;
typedef std::shared_ptr<ciScrollView> ciScrollViewRef;

class ciScrollView : public coc::ScrollView {

public:

    static ciScrollViewRef create() { return ciScrollViewRef(new ciScrollView()); }
    virtual coc::ButtonRef initButton() const override { return coc::ciButton::create(); }

	void begin() override;
	void end() override;

protected:

    //

};

}

#endif


