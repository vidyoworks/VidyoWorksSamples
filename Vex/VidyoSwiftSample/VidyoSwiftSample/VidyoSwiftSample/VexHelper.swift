//
//  VexHelper.swift
//  VidyoSwiftSample
//
//  Created by Dinesh Sinha on 4/7/18.
//  Copyright © 2018 Vidyo. All rights reserved.
//

import Foundation

import Alamofire
import SwiftyJSON
import AlamofireObjectMapper


class User
{
    var firstName:String = ""
}

class Appointment
{
    var scheduleToken:String = ""
}

class VidyoCredentials
{
    var tenant:String = ""
}

typealias InteractionStatus = String


class VexHelper {
    
    static let BASE_URL = "https://vex.vidyoclouddev.com/v2/"
    static let TENANT = "64"
    
    static let POLL_TIME_INTERVAL_IN_SECONDS = 10
    static let POLL_TIME_TOTAL_IN_SECONDS = 60 * 15 // 60 seconds (1 minute) * 15 = 15 minutes, which is the token life
	static var m_tokens: (daytoken:String, token:String)?
    static var m_ScheduleParams: (serverUrl:String, tenantId:String, agentId:String, customerName:String, scheduleToken:String)?
    static var m_interactionToken = ""
	static func joinVexScheduledCall(scheduleLink:String) {
		// valid schedule link example:
		let tmpScheduleLink = "https://apps.vidyoclouddev.com/vex/vidyo/2/interaction/schedule.html?scheduleString=dG9rZW49ODBIdTFudXYmdGVuYW50SWQ9MTMzJnNlcnZlclVSTD1odHRwczovL3ZleC52aWR5b2Nsb3VkZGV2LmNvbSZhZ2VudElkPWRvY3RvcjEmY05hbWU9U2NoZWR1bGUgQ2FsbCBPbmUmYXBpS2V5PVVwVE5Mc0JmSnh3WnJ3Qmo="
		//
		
		// 1. Parse schedule string, Extract server url, tenant id, agent id and customer name from decodedStr
		m_ScheduleParams = parseScheduleUrl(scheduleUrl: tmpScheduleLink)
		
		// 2.
        GetCustomerProfile(serverUrl: (m_ScheduleParams?.serverUrl)!, tenantId: (m_ScheduleParams?.tenantId)!)
       
        
		
		// 3. Add/request interaction based passing in the above values
		
		
		// 4. Start polling for interactions status (checkInteraction, wait while Agent accepts a call)
		
		// 5. Receive roomUrl, extract roomKey
		
		// 6. Join a call

	}
    
    static func parseScheduleUrl(scheduleUrl:String) -> (serverUrl:String, tenantId:String, agentId:String, customerName:String, scheduleToken: String) {
		// Extract schedule string
		let parts = scheduleUrl.components(separatedBy: "?scheduleString=");
		var scheduleString = "";
		if (parts.count > 1){
			scheduleString = parts[1]
		}
		
		// Decode schedule string
		var decodedStr = "";
		if (!scheduleString.isEmpty){
			let decodedData = Data(base64Encoded: scheduleString)!
			decodedStr = String(data: decodedData, encoding: .utf8)!
		}
		
		// Get return values
		let arr = decodedStr.split(separator: "&");
        
        var params = [String : String]()
        for arrobject in arr {
            let arrProperty = arrobject.split(separator: "=")
            if(arrProperty.count < 2)
            {
                continue
            }
            let entry = String(describing: arrProperty[0])
            let value = String(describing: arrProperty[1])
            params[entry] = value
        }
        
		
		return (params["serverURL"]!, params["tenantId"]!, params["agentId"]!, params["cName"]!, params["token"]!)
	}
	
	static func GetCustomerProfile(serverUrl:String, tenantId:String)
    {
        let CUSTOMER_PROFILE = "customerProfile?tenant="
        var daytoken:String = "";
        var token:String = "";
         
		let url = "\(serverUrl)/v2/\(CUSTOMER_PROFILE)\(tenantId)"
		//let url = "\(serverUrl)/v2/\(CUSTOMER_PROFILE)\(TENANT)"
        Alamofire.request(url).responseJSON { response in
                print("Request: \(String(describing: response.request))")
                print("Response: \(String(describing: response.response))")
                print("Result: \(response.result)")
            
            if let json = response.result.value {
                print("JSON: \(json)") // serialized json response
            }
            
            print("All headers - \(String(describing: response.response?.allHeaderFields))")
            
            
            if let daytokentmp = response.response?.allHeaderFields["DayToken"] as? String {
                daytoken = daytokentmp
                print("JSON: \(daytoken)") // serialized json response
            }
            
            
            if  let tokentmp = response.response?.allHeaderFields["Token"] as? String {
                token = tokentmp
                print("JSON: \(token)") // serialized json response
                
                VexHelper.m_tokens = (String(daytoken), String(token))
                
                addInteraction()
            }
                /*if let data = response.data, let utf8Text = String(data: data, encoding: .utf8) {
                    print("Data: \(utf8Text)") // original server data as UTF8 string
                }*/
            }
    }
    
    
    
    static func addInteraction(){
        
        //dinesh to do
        let schedule = (m_ScheduleParams?.scheduleToken)! != nil ? "true" : "false"
        
        
        var params = [String : Any]()
        params["tenant"] = (m_ScheduleParams?.tenantId)!
        
        params["xmlBlob"] = "<SERVICE><userName>\((m_ScheduleParams?.customerName)!)</userName><schedule>\(schedule)</schedule></SERVICE>"
        
      
        params["agentId"] = (m_ScheduleParams?.agentId)!
        
        let ADD_INTERACTION = "interactions?tenant="
       
        
        let url = "\((m_ScheduleParams?.serverUrl)!)/v2/\(ADD_INTERACTION)\((m_ScheduleParams?.tenantId)!)"
        
        let header:HTTPHeaders =  [
        "daytoken": (m_tokens?.daytoken)!,
        "token": (m_tokens?.token)!
        ]
        
        
        
        
        Alamofire.request(url, method: .post, parameters: params, encoding: JSONEncoding.default, headers: header).responseJSON { response in
            print("Request: \(String(describing: response.request))")
            print(NSString(data: (response.request?.httpBody)!, encoding: String.Encoding.utf8.rawValue))
            //print(NSString(data: (response.request?.allHTTPHeaderFields)!, encoding: String.Encoding.utf8.rawValue))
            //print("Request All headers - \(String(describing: request?.allHeaderFields))")
            print("Response: \(String(describing: response.response))")
            print("Result: \(response.result)")
            
            let existingHeaders = response.request?.allHTTPHeaderFields
            print("token: \((existingHeaders!["token"])!)")
            print("daytoken: \((existingHeaders!["daytoken"])!)")
            
            //let json = response as! NSDictionary
            //m_interactionToken = json.object(forKey: "interactionToken")! as! String
            
            var helloWorldTimer = Timer.scheduledTimer(timeInterval: 60.0, target: self, selector: Selector("callCheckInteraction"), userInfo: nil, repeats: true)
            
            if let json = response.result.value {
                print("JSON: \(json)") // serialized json response
            }
        }
    }
    
    static func callCheckInteraction()
    {
        checkInteraction();
    }
    
    static func checkInteraction()
    {
        
        var params = [String : Any]()
        params["source"] = "CUSTOMER"
        params["tenant"] = (m_ScheduleParams?.tenantId)!
        //need to set interaction
        params["interactionToken"] = m_interactionToken
        
      
        
        let CHECK_INTERACTION = "interactions/checkInteraction/?tenant="
        
        
        let url = "\((m_ScheduleParams?.serverUrl)!)/v2/\(CHECK_INTERACTION)\((m_ScheduleParams?.tenantId)!)"
        
        let header:HTTPHeaders =  [
            "daytoken": (m_tokens?.daytoken)!,
            "token": (m_tokens?.token)!
        ]
        
        
        
        
        Alamofire.request(url, method: .get, parameters: params, encoding: JSONEncoding.default, headers: header).responseJSON { response in
            print("Request: \(String(describing: response.request))")
            print(NSString(data: (response.request?.httpBody)!, encoding: String.Encoding.utf8.rawValue))
            //print(NSString(data: (response.request?.allHTTPHeaderFields)!, encoding: String.Encoding.utf8.rawValue))
            //print("Request All headers - \(String(describing: request?.allHeaderFields))")
            print("Response: \(String(describing: response.response))")
            print("Result: \(response.result)")
            
            let existingHeaders = response.request?.allHTTPHeaderFields
            print("token: \((existingHeaders!["token"])!)")
            print("daytoken: \((existingHeaders!["daytoken"])!)")
            
            let json = response as! NSDictionary
            let interactionPickedTime = json.object(forKey: "interactionPickedTime")! as! String
            if(!interactionPickedTime.isEmpty)
            {
                let roomLink = json.object(forKey: "vidyoGuestURL")! as! String
            }
           
            
            if let json = response.result.value {
                print("JSON: \(json)") // serialized json response
            }
        }
    }
    
}
