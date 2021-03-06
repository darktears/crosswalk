// Copyright (c) 2013 Intel Corporation. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

package org.xwalk.app.runtime;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.util.AttributeSet;
import android.widget.LinearLayout;

/**
 * This class is to provide public APIs which are called by web application
 * APKs. Since the runtime is shared as a library APK, web application APKs
 * have to call them via class loader but not direct API calling.
 *
 * A web application APK should create its Activity and set this view as
 * its content view.
 */
// Implementation notes.
// Please be careful to change any public APIs for the backward compatibility
// is very important to us. Don't change any of them without permisson.
public class XWalkRuntimeView extends LinearLayout {
    // The actual implementation to hide the internals to API users.
    private XWalkRuntimeViewProvider mProvider;

    /**
     * Contructs a XWalkRuntimeView with Activity and library Context. Called
     * from runtime client.
     *
     * @param activity the activity from runtime client
     * @param context a context when creating this package
     * @param attrs the attributes of the XML tag that is inflating the view
     */
    public XWalkRuntimeView(Activity activity, Context context, AttributeSet attrs) {
        super(context, attrs);

        // MixedContext is needed for cross package because the application
        // context is different.
        init(context, activity);
    }

    /**
     * This is for inflating this view from XML. Called from test shell.
     * @param context a context to construct View
     * @param attrs the attributes of the XML tag that is inflating the view
     */
    public XWalkRuntimeView(Context context, AttributeSet attrs) {
        super(context, attrs);

        init(context, (Activity)context);
    }

    private void init(Context context, Activity activity) {
        mProvider = XWalkRuntimeViewProviderFactory.getProvider(context, activity);
        setOrientation(LinearLayout.VERTICAL);
        this.addView(mProvider.getView(),
                new LinearLayout.LayoutParams(
                        LinearLayout.LayoutParams.MATCH_PARENT,
                        LinearLayout.LayoutParams.MATCH_PARENT));
    }

    /**
     * Get the version information of current runtime library.
     *
     * @return the string containing the version information.
     */
    public String getVersion() {
        return mProvider.getVersion();
    }

    /**
     * Load a web application through the entry url. It may be
     * a file from assets or a url from network.
     *
     * @param url the url of loaded html resource.
     */
    public void loadAppFromUrl(String url) {
        mProvider.loadAppFromUrl(url);
    }

    /**
     * Load a web application through the url of the manifest file.
     * The manifest file typically is placed in android assets. Now it is
     * compliant to W3C SysApps spec.
     *
     * @param manifestUrl the url of the manifest file
     */
    public void loadAppFromManifest(String manifestUrl) {
        mProvider.loadAppFromManifest(manifestUrl);
    }

    /**
     * Tell runtime that the application is on creating. This can make runtime
     * be aware of application life cycle.
     */
    public void onCreate() {
        mProvider.onCreate();
    }

    /**
     * Tell runtime that the application is on resuming. This can make runtime
     * be aware of application life cycle.
     */
    public void onResume() {
        mProvider.onResume();
    }

    /**
     * Tell runtime that the application is on pausing. This can make runtime
     * be aware of application life cycle.
     */
    public void onPause() {
        mProvider.onPause();
    }

    /**
     * Tell runtime that the application is on destroying. This can make runtime
     * be aware of application life cycle.
     */
    public void onDestroy() {
        mProvider.onDestroy();
    }

    /**
     * Tell runtime that the activity receive a new Intent to start it. It may contains
     * data that runtime want to deal with.
     * @param intent the new coming Intent.
     * @return boolean whether runtime consumed it.
     */
    public boolean onNewIntent(Intent intent) {
        return mProvider.onNewIntent(intent);
    }

    /**
     * Enable remote debugging for the loaded web application. The caller
     * can set the url of debugging url. Besides, the socket name for remote
     * debugging has to be unique so typically the string can be appended
     * with the package name of the application.
     *
     * @param frontEndUrl the url of debugging url. If it's empty, then a
     *                    default url will be used.
     * @param socketName the unique socket name for setting up socket for
     *                   remote debugging. If it's empty, then a default
     *                   name will be used.
     * @return the url of web socket for remote debugging
     */
    public void enableRemoteDebugging(String frontEndUrl, String socketName) {
        // TODO(yongsheng): Figure out which parameters are needed once we
        // have a conclusion.
        mProvider.enableRemoteDebugging(frontEndUrl,socketName);
    }

    /**
     * Disable remote debugging so runtime can close related stuff for
     * this feature.
     */
    public void disableRemoteDebugging() {
        mProvider.disableRemoteDebugging();
    }

    // For instrumentation test.
    public String getTitleForTest() {
        return mProvider.getTitleForTest();
    }

    public void setCallbackForTest(Object callback) {
        mProvider.setCallbackForTest(callback);
    }

    public void loadDataForTest(String data, String mimeType, boolean isBase64Encoded) {
        mProvider.loadDataForTest(data, mimeType, isBase64Encoded);
    }

    public void loadExtensions() {
        mProvider.loadExtensions();
    }
}
