<?php

/*
    Disables the local cache; Use during development.
    Should be turned OFF for production otherwise might impact performance
*/
ini_set("soap.wsdl_cache_enabled", "0");

/* SOAP parameters */
$dataObj = $_GET['soapBody'];

/* Check if all mandatory parameters are there */
if (!array_key_exists('soapAction', $_GET) ||
    !array_key_exists('soapServerUrl', $_GET) ||
    !array_key_exists('soapServicePath', $_GET) ||
    !array_key_exists('soapServiceUsername', $_GET) ||
    !array_key_exists('soapServicePassword', $_GET))
{
    header(':', true, 200);
    $errors = array();
    if (!array_key_exists('soapAction', $_GET)) {
        $errors['soapAction'] .= 'Not set';
    }
    if(!array_key_exists('soapServerUrl', $_GET)) {
        $errors['soapServerUrl'] .= 'Not set';
    }
    if(!array_key_exists('soapServicePath', $_GET)) {
        $errors['soapServicePath'] .= 'Not set';
    }
    if(!array_key_exists('soapServiceUsername', $_GET)) {
        $errors['soapServiceUsername'] .= 'Not set';
    }
    if(!array_key_exists('soapServicePassword', $_GET)) {
        $errors['soapServicePassword'] .= 'Not set';
    }


    respondWithData(json_encode(array(
            "success" => false,
            "general_message" => "Bad parameters",
            "errors" => $errors
            )));
    exit();
}

$resp = performSoapRequest($_GET['soapServerUrl'], $_GET['soapServicePath'], $_GET['soapServiceUsername'], $_GET['soapServicePassword'], $_GET['soapAction'], $dataObj);

respondWithData(json_encode($resp));

/**
 * Sends a SOAP request
 * @param  string $soapServerURL    URL of the SOAP server
 * @param  string $serviceUrl       Path to a SOAP service relative to URL above
 * @param  string $username         Authentication name of the user
 * @param  string $password         Authentication secret
 * @param  string $action           SOAP action to perform
 * @param  array $data              Data for the SOAP request body
 * @return array                    Result array
 */
function performSoapRequest($soapServerURL, $serviceUrl, $username, $password, $action, $data) {

    // Create the Soap Client
    try {

        $client = new SoapClient($soapServerURL . $serviceUrl,
         array('login' => $username,
               'password' => $password,
               'trace' => TRUE,
               'exceptions' => TRUE,
               'soap_version' => SOAP_1_2));

        $resp = $client->{$action}($data);
    }
    catch (Exception $e) {
        header(':', true, 200);
        return array(
            "success" => false,
            "message" => "SOAP failure",
            "errors" => $e);
    }

    return array(
            "success" => true,
            "message" => "",
            "response" => $resp);
}

/**
 * Sends a response to an ajax request
 * @param  array $data response data
 * @return None
 */
function respondWithData($data)
{
    if(array_key_exists('callback', $_GET)){

        header('Content-Type: text/javascript; charset=utf8');
        header('Access-Control-Allow-Origin: *');
        header('Access-Control-Max-Age: 3628800');
        header('Access-Control-Allow-Methods: GET, POST');

        $callback = $_GET['callback'];
        echo $callback.'('.$data.');';

    }
    else {
        // normal JSON string
        header('Access-Control-Allow-Origin: *');
        header('Access-Control-Max-Age: 3628800');
        header('Access-Control-Allow-Methods: GET, POST');
        header('Content-Type: application/json; charset=utf8');

        echo $data;
    }
}
