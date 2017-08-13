/**
 * @fileOverview This file defines SOAP proxy utility class to be used with soap_proxy.php script.
 * @author Vidyo Inc.
 * @version 1.0.0
 */
/*jslint browser: true, indent : 4, nomen : true, vars: true, maxerr : 10 */
/*global requirejs: false, bootstrap: false, handlebars: false, define: false, jquery: false, jQuery: false, Handlebars: false */

(function () {
    "use strict";
    define(["jquery"], function ($) {
        var soapClient = function () {
            /** @private */
            var self = {};
            /**
             * Configuration object
             * @type {Object}
             */
            var config = {
                /**
                 * AJAX request dataType. Could be 'json' or 'jsonp'.
                 * @type {String}
                 */
                ajaxDataType: 'jsonp',
                /**
                 * URL of proxy server (http://DOMAIN/soap_proxy.php)
                 * @type {String}
                 */
                proxyUrl: undefined,
                /**
                 * SOAP method/action (getParticipants)
                 * @type {String}
                 */
                soapAction: undefined,
                /**
                 * SOAP URL of SOAP server (http://SOAP_SERVER)
                 * @type {String}
                 */
                soapServerUrl: undefined,
                /**
                 * Path to SOAP service relative to soapServerUrl (/services/MyService?wsdl)
                 * @type {String}
                 */
                soapServicePath: undefined,
                /**
                 * Username on SOAP server
                 * @type {String}
                 */
                soapServiceUsername: undefined,
                /**
                 * Password on SOAP server
                 * @type {String}
                 */
                soapServicePassword: undefined,
                /**
                 * JSON object with SOAP body ({query: 'hello'})
                 * @type {Object}
                 */
                soapBody: undefined,
                /**
                 * Function that will be called on success
                 * @type {String}
                 */
                onSuccess: undefined,
                /**
                 * Function that will be called on failure
                 * @type {String}
                 */
                onFailure: undefined
            };

            /**
             * Initialize soap proxy with configuration
             * @param  {Object} config Configuration parameter
             * @return {Object}      Returns self
             */
            var init = function (config) {
                self.config = $.extend({}, self.config, config);
                return self;
            };

            /**
             * Sends a soap request
             * @private
             * @param  {String} proxyUrl            URL of proxy server (http://DOMAIN/soap_proxy.php)
             * @param  {String} soapAction          SOAP method/action (getParticipants)
             * @param  {String} soapServerUrl       URL of SOAP server (http://SOAP_SERVER)
             * @param  {String} soapServicePath     Path to SOAP service relative to soapServerUrl (/services/MyService?wsdl)
             * @param  {String} soapServiceUsername Username on SOAP server
             * @param  {String} soapServicePassword Password on SOAP server
             * @param  {Object} soapBody            JSON object with SOAP body ({query: 'hello'})
             * @param  {Function} onSuccess         Optional function that will be called on success
             * @param  {Function} onFailure         Optional function that will be called on failure
             * @return {jQuery.Deferred object}     Deffered object that can accept .done and .fail functions
             */
            var _postSoapRequest = function (
                proxyUrl,
                soapAction,
                soapServerUrl,
                soapServicePath,
                soapServiceUsername,
                soapServicePassword,
                soapBody,
                onSuccess,
                onFailure,
                dataType,
                defferedParam) {
                return $.ajax({
                    url: proxyUrl,
                    data: {
                        soapAction: soapAction,
                        soapServerUrl: soapServerUrl,
                        soapServicePath: soapServicePath,
                        soapServiceUsername: soapServiceUsername,
                        soapServicePassword: soapServicePassword,
                        soapBody: soapBody
                    },
                    dataType: dataType || 'jsonp',
                    crossDomain: true,
                    type: 'GET'
                })
                    .done(function (result) {
                        if (result.success === false) {
                            defferedParam.reject(result.message, result.errors);
                            if (onFailure !== undefined) {
                                onFailure.call(self, result.message, result.errors);
                            }
                        } else if (result.response.faultcode !== undefined) {
                            defferedParam.reject(result.response, result.response);
                            if (onFailure !== undefined) {
                                onFailure.call(self, result.response, result.response);
                            }
                        } else {
                            defferedParam.resolve(result.response);
                            if (onSuccess) {
                                onSuccess.call(self, result.response);
                            }
                        }
                    })
                    .fail(function (result) {
                        console.warn('result', JSON.stringify(arguments));
                        defferedParam.reject("AJAX failure", result.statusText);
                        if (onFailure !== undefined) {
                            onFailure.call(self, "AJAX failure", result.statusText);
                        }
                    });

            };
            /**
             * Perform a soap request
             * @param  {Object} config      See self.config object
             * @return {Object}        Deferred object
             */
            var request = function (config) {
                var opt = $.extend({}, self.config, config);

                //console.log('config', config);

                if (opt.proxyUrl === undefined ||
                    opt.soapServerUrl === undefined ||
                    opt.soapServicePath === undefined ||
                    opt.soapServiceUsername === undefined ||
                    opt.soapServicePassword === undefined ||
                    opt.soapBody === undefined) {
                    var def = $.Deferred();
                    def.reject();
                    if (opt.onFailure !== undefined) {
                        opt.onFailure.call(this);
                    }
                    return def;
                }
                var defferedParam = $.Deferred();
                var request = _postSoapRequest(
                    opt.proxyUrl,
                    opt.soapAction,
                    opt.soapServerUrl,
                    opt.soapServicePath,
                    opt.soapServiceUsername,
                    opt.soapServicePassword,
                    opt.soapBody,
                    opt.onSuccess,
                    opt.onFailure,
                    opt.ajaxDataType,
                    defferedParam);
                var promise = defferedParam.promise();
                promise.request = request;
                return promise;
            };

            init(config);
            self.request = request;
            return self;
        };

        return soapClient;
    });
}());