/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.
 
http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package org.cocos2dx.cpp;

import org.cocos2dx.lib.Cocos2dxActivity;

import com.umeng.social.CCUMSocialController;

import android.content.Context;
import android.content.Intent;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.os.Bundle;

public class AppActivity extends Cocos2dxActivity 
{
	public static AppActivity s_Instance;
	  protected void onCreate(Bundle savedInstanceState)
	 {
		 s_Instance = this;
		  
	 	 super.onCreate(savedInstanceState);
	 	 CCUMSocialController.initSocialSDK(this, "com.umeng.social.share");
	 }	
	 
	 public void onActivityResult(int requestCode, int resultCode, Intent data)
	 {
	 	CCUMSocialController.onActivityResult(requestCode, resultCode, data);         
	 	super.onActivityResult(requestCode, resultCode, data);
	 }

	 
	  /*public boolean isNetworkConnected() {
		  boolean bIsNetworkConnected = false;
		  final Context context = getApplicationContext();
		  if(context == null)
		  {
			  return false;
		  }
		  ConnectivityManager cm = (ConnectivityManager) context.getSystemService(Context.CONNECTIVITY_SERVICE);
	        NetworkInfo ni = cm.getActiveNetworkInfo();
	        return ni != null && ni.isConnectedOrConnecting();
    }*/
	 public static boolean isNetworkConnected() {
			ConnectivityManager mConnectivityManager = (ConnectivityManager) s_Instance
					.getSystemService(Context.CONNECTIVITY_SERVICE);
			NetworkInfo mNetworkInfo = mConnectivityManager.getActiveNetworkInfo();
			if (mNetworkInfo != null) {
				return mNetworkInfo.isAvailable();
			}
			return false;
   }

	 static {
	      System.loadLibrary("eventcore");
	 }
}