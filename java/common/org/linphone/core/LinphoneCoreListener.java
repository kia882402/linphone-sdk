/*
LinphoneCoreListener.java
Copyright (C) 2010  Belledonne Communications, Grenoble, France

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */
package org.linphone.core;


/**
 * 
 *This interface holds all callbacks that the application should implement. None is mandatory.
 */
public interface LinphoneCoreListener {

	/**< Notifies the application that it should show up
	 * @return */
	void show(LinphoneCore lc);

	/**< Ask the application some authentication information 
	 * @return */
	void authInfoRequested(LinphoneCore lc,String realm,String username); 

	/**< Callback that notifies various events with human readable text.
	 * @return */
	void displayStatus(LinphoneCore lc,String message);

	/**< Callback to display a message to the user 
	 * @return */
	void displayMessage(LinphoneCore lc,String message);

	/** Callback to display a warning to the user 
	 * @return */
	void displayWarning(LinphoneCore lc,String message);

	/** General State notification  
	 * @param state LinphoneCore.State
	 * @return 
	 * */		
	void globalState(LinphoneCore lc,LinphoneCore.GlobalState state, String message);

	/** Call  State notification  
	 * @param state LinphoneCall.State
	 * @return 
	 * */		
	void callState(LinphoneCore lc, LinphoneCall call, LinphoneCall.State cstate,String message);

	/**
	 * Callback to display change in encryption state.
	 * @param encrypted true if all streams of the call are encrypted
	 * @param authenticationToken token like ZRTP SAS that may be displayed to user
	 */
	void callEncryptionChanged(LinphoneCore lc, LinphoneCall call, boolean encrypted, String authenticationToken);

	/**
	 * Registration state notification
	 * */
	void registrationState(LinphoneCore lc, LinphoneProxyConfig cfg, LinphoneCore.RegistrationState cstate, String smessage);

	/**
	 * Reports that a new subscription request has been received and wait for a decision. 
	 *Status on this subscription request is notified by changing policy for this friend
	 *@param lc LinphoneCore 	
	 *@param lf LinphoneFriend corresponding to the subscriber
	 *@param url of the subscriber
	 * 
	 */
	void newSubscriptionRequest(LinphoneCore lc, LinphoneFriend lf, String url);

	/**
	 * Report status change for a friend previously added to LinphoneCore.
	 * @param lc LinphoneCore
	 * @param lf updated LinphoneFriend
	 */
	void notifyPresenceReceived(LinphoneCore lc, LinphoneFriend lf);

	/**
	 * invoked when a new text message is received
	 * @param lc LinphoneCore
	 * @param  room 	LinphoneChatRoom involved in this conversation. Can be be created by the framework in case the from is not present in any chat room.
	 * @param from  	LinphoneAddress from
	 * @param message 	incoming message
	 */
	void textReceived(LinphoneCore lc, LinphoneChatRoom cr,LinphoneAddress from,String message);

	/**
	 * Invoked when echo cancalation calibration is completed
	 * @param lc LinphoneCore
	 * @param status 
	 * @param delay_ms echo delay
	 * @param data
	 */
	void ecCalibrationStatus(LinphoneCore lc,LinphoneCore.EcCalibratorStatus status, int delay_ms, Object data);
}

