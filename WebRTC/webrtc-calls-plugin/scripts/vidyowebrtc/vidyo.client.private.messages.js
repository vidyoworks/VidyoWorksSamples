/*! @file vidyo.client.private.messages.js
                @VidyoWeb API Library header.
                @copyright
                (c) 2012-2014 Vidyo, Inc.
                433 Hackensack Avenue, 7th Floor,
                Hackensack, NJ  07601.
                All rights reserved.
                The information contained herein is proprietary to Vidyo, Inc.
                and shall not be reproduced, copied (in whole or in part), adapted,
                modified, disseminated, transmitted, transcribed, stored in a retrieval
                system, or translated into any language in any form by any means
                without the express written consent of Vidyo, Inc.
*/

/**
  * @fileOverview This file defines the module for the private VidyoClient message objects.
  * @author Vidyo Inc.
  */

var vidyoClientPrivateMessages =  {
    /**
     * Creates a VidyoClient private message object.
     *
     * @param {string} type String value for specific type of message.
     * @return {Object} Reference to created object.
     */
    'privateMessage': function (type) {
        // object created by this factory function
        var that = {};

        // public properties for created object
        that.type = type;

        // return object created by this factory function
        return that;
    },

    /**
     * Creates a VidyoClient private in event object, for event messages
     * which flow into VidyoClient, but are not published.
     *
     * @param {string} type String value for specific type of message.
     * @return {Object} Reference to created object.
     */
    'privateInEvent': function (type) {
        // object created by this factory function
        var that = this.privateMessage(type);

        // return object created by this factory function
        return that;
    },

    /**
     * Creates a VidyoClient private VCSOAP in event object.
     * Used to communicate with VidyoPortal via VCSOAP protocol.
     *
     * The passed in parameter object can store the following
     * properties:
     *  - typeRequest (various)
     *  - requestId (should be unique for each request)
     *
     * @param {string} type String value for specific type of message.
     * @param {Object} params Reference to parameter object.
     * @return {Object} Reference to created object.
     */
    'privateInEventVcsoap': function (type, params) {
        // object created by this factory function
        var that = this.privateInEvent(type);

        // public properties for created object,
        // initial values of which are potentially passed
        // into this factory function
        that.typeRequest = params && params.typeRequest || "";
        that.requestId = params && params.requestId || 0;

        // return object created by this factory function
        return that;
    },

    /**
     * Creates a VidyoClient private VCSOAP in event object.
     * Used to initiate guest login with VidyoPortal via VCSOAP protocol.
     *
     * The passed in parameter object can store the following
     * properties:
     *  - requestId (should be unique for each request)
     *  - portalUri
     *  - roomKey
     *  - guestName
     *  - pin
     *
     * @param {Object} params Reference to parameter object.
     * @return {Object} Reference to created object.
     */
    'privateInEventVcsoapGuestLink': function (params) {
        // object created by this factory function
        params = params || {};
        params.typeRequest = "GuestLink";
        var that = this.privateInEventVcsoap("PrivateInEventVcsoapGuestLink", params);

        // public properties for created object,
        // initial values of which are potentially passed
        // into this factory function
        that.portalUri = params && params.portalUri || "";
        that.roomKey = params && params.roomKey || "";
        that.guestName = params && params.guestName || "";
        that.pin = params && params.pin || "";

        // return object created by this factory function
        return that;
    },

}
