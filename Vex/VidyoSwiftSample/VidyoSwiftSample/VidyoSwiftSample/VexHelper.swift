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


class VexHelper {
    
    static let BASE_URL = "https://vex.vidyoclouddev.com/v2/"
    static let TENANT = "64"
    
    static let POLL_TIME_INTERVAL_IN_SECONDS = 10
    static let POLL_TIME_TOTAL_IN_SECONDS = 60 * 15 // 60 seconds (1 minute) * 15 = 15 minutes, which is the token life
	static var m_tokens: (daytoken:String, token:String)?
    static var m_ScheduleParams: (serverUrl:String, tenantId:String, agentId:String, customerName:String)?
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
    
	static func parseScheduleUrl(scheduleUrl:String) -> (serverUrl:String, tenantId:String, agentId:String, customerName:String) {
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
        
		
		return (params["serverURL"]!, params["tenantId"]!, params["agentId"]!, params["cName"]!)
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
                
                AddInteraction(serverUrl: (serverUrl), tenantId: (tenantId))
            }
                /*if let data = response.data, let utf8Text = String(data: data, encoding: .utf8) {
                    print("Data: \(utf8Text)") // original server data as UTF8 string
                }*/
            }
    }
    
    
    static func AddInteraction(serverUrl:String, tenantId:String)
    {
        print("token: \(String(describing: m_tokens?.token))")
        print("daytoken: \(String(describing: m_tokens?.daytoken))")
        /*let CUSTOMER_PROFILE = "customerProfile?tenant="
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
            }
 
        }*/
    }
    
    
    
	static func connect()
	{
		/*Alamofire.request("https://vex.vidyoclouddev.com/v2/customerProfile?tenant=64").responseJSON { response in
		print("Request: \(String(describing: response.request))")   // original url request
		print("Response: \(String(describing: response.response))") // http url response
		print("Result: \(response.result)")                         // response serialization result
		
		if let json = response.result.value {
		print("JSON: \(json)") // serialized json response
		}
		
		if let data = response.data, let utf8Text = String(data: data, encoding: .utf8) {
		print("Data: \(utf8Text)") // original server data as UTF8 string
		}
		}*/
		//GetCustomerProfile();
	}
    
    // handles connecting a user to a call
    /*static func connect(user:User, forAppointment appointment:Appointment, onWaitingRoomJoined: @escaping (_ waitingRoomVideo:WaitingRoomVideo?) -> Void, onConnected: @escaping (_ interaction:InteractionStatus) -> Void, onError: @escaping (_ error:String) -> Void){
        
        // get a token we can use to query against other vidyoServices
        getVidyoCredentials(
            user: user,
            onSuccess: { (token, vidyoCredentials) in
                
                // create the interaction (basically a room the randox agent can see/join)
                addInteraction(
                    token: token,
                    vidyoCredentials: vidyoCredentials,
                    forUser: user,
                    appointment: appointment,
                    onSuccess: { (interaction) in
                        
                        // seeing as we have created an interaction and are waiting for a doctor
                        // we can inform user that we've joined a waiting room, first we need to get
                        // the waiting room video
                        getWaitingRoomVideo(token: token,
                                            withVidyoCredentials: vidyoCredentials,
                                            onWaitingVideoFound: { (waitingRoomVideo) in
                                                onWaitingRoomJoined(waitingRoomVideo)
                        },
                                            onError: { (error) in
                                                // if we run into an error we can still notify the user
                                                // that we're in a waiting room
                                                onWaitingRoomJoined(nil)
                        })
                        
                        // how long we'll keep maintaining the interaction before giving up
                        let pollAttemptsRemaining = VexHelper.POLL_TIME_TOTAL_IN_SECONDS / VexHelper.POLL_TIME_INTERVAL_IN_SECONDS
                        
                        // we've created an interaction (waiting room) and now need to keep it
                        // alive until randox agent/doctor joins
                        maintain(
                            interaction: interaction,
                            withToken: token,
                            withVidyoCredentials: vidyoCredentials,
                            pollAttemptsRemaining: pollAttemptsRemaining,
                            onConnected: onConnected,
                            onError: onError)
                        
                },
                    onError: onError)
        },
            onError: onError)
    }
    
    static func getVidyoCredentials(user:User, onSuccess: @escaping (_ token:String, _ vidyoCredentials:VidyoCredentials) -> Void, onError: @escaping (_ error:String) -> Void){
        
        let url = "\(DatabaseHelper.baseUrl)Appointments/Telemedicine/GetConfigSettings"
        let header:HTTPHeaders = AuthManager.getDefaultHeaders(user.objectId)
        Alamofire.request(url, method: .get, headers: header)
            .responseObject { (response: DataResponse<VidyoCredentials>) in
                
                guard let vidyoCredentials = response.result.value else {
                    onError("An unexpected errror occured, please try again later.")
                    return
                }
                
                let url = "\(BASE_URL)customerProfile?tenant=\(vidyoCredentials.tenant!)&access_token=\(vidyoCredentials.apiKey!)"
                Alamofire.request(url, method: .get)
                    .responseObject { (response: DataResponse<CustomerProfile>) in
                        var customerProfile = response.result.value
                        guard let token = response.response?.allHeaderFields["Token"] as? String else {
                            onError("An unexpected error occured, please try again later.")
                            return
                        }
                        
                        onSuccess(token, vidyoCredentials)
                }
        }
    }
    static func addInteraction(token: String, vidyoCredentials:VidyoCredentials, forUser user:User, appointment:Appointment, onSuccess: @escaping (_ interaction:InteractionStatus) -> Void, onError: @escaping (_ error:String) -> Void){
        
        let schedule = appointment.scheduleToken != nil ? "true" : "false"
        
        var params = [String : Any]()
        params["tenant"] = vidyoCredentials.tenant
        params["xmlBlob"] = "<SERVICE><userName>\(user.firstName)</userName><schedule>\(schedule)</schedule></SERVICE>"
        
        //        if let vidyoAgentId = appointment.vidyoAgentId {
        //            params["agentId"] = vidyoAgentId
        //        }
        params["agentId"] = "doctor1"
        
        
        let url = get(urlWithEndpoint: "interactions", withVidyoCredentials: vidyoCredentials)
        let header:HTTPHeaders = getHeaders(token)
        
        Alamofire.request(url, method: .post, parameters: params, encoding: JSONEncoding.default, headers: header)
            .responseObject { (response: DataResponse<InteractionStatus>) in
                
                guard let interactionStatus = response.result.value else {
                    print(response.error)
                    onError("An unexpected error occured, please try again later.")
                    return
                }
                
                onSuccess(interactionStatus)
        }
    }
    static func check(interaction:InteractionStatus, withToken token:String, withVidyoCredentials vidyoCredentials:VidyoCredentials, onSuccess: @escaping (_ interactionStatus:InteractionStatus) -> Void, onError: @escaping (_ error:String) -> Void){
        
        var params = [String : Any]()
        params["tenant"] = vidyoCredentials.tenant
        params["interactionToken"] = interaction.interactionToken
        params["source"] = "CUSTOMER"
        
        let header:HTTPHeaders = getHeaders(token)
        let url = get(urlWithEndpoint: "interactions/checkInteraction", withVidyoCredentials: vidyoCredentials)
        Alamofire.request(url, method: .get, parameters: params, headers: header)
            .responseObject { (response: DataResponse<InteractionStatus>) in
                
                guard let interactionStatus = response.result.value else {
                    onError("An unexpected error occured, please try again later.")
                    return
                }
                print("updated interaction")
                onSuccess(interactionStatus)
        }
    }
    // is this function necessary? will we ever have another agentId to switch to?
    static func update(token:String, interaction:InteractionStatus, withVidyoCredentials vidyoCredentials:VidyoCredentials, withNewAgentId agentId:String, andNewSkillSet skillSet:String, onSuccess: @escaping (_ InteractionStatus:InteractionStatus) -> Void, onError: @escaping (_ error:String) -> Void){
        
        var params = [String : Any]()
        params["tenant"] = vidyoCredentials.tenant
        params["interactionToken"] = interaction.interactionToken
        params["agentId"] = agentId
        params["skillset"] = skillSet
        
        let header:HTTPHeaders = getHeaders(token)
        let url = get(urlWithEndpoint: "interactions/updateInteraction", withVidyoCredentials: vidyoCredentials)
        Alamofire.request(url, method: .put, parameters: params, headers: header)
            .responseObject { (response: DataResponse<InteractionStatus>) in
                
                guard let interactionStatus = response.result.value else {
                    onError("An unexpected error occured, please try again later.")
                    return
                }
                
                onSuccess(interactionStatus)
        }
    }
    
    // maintains an interaction until randox agent answers or times out
    static func maintain(interaction:InteractionStatus, withToken token:String, withVidyoCredentials vidyoCredentials:VidyoCredentials, pollAttemptsRemaining:Int, onConnected: @escaping (_ interaction:InteractionStatus) -> Void, onError: @escaping (_ error:String) -> Void){
        
        // check if a doctor has joined the interaction
        // in which case we can report success and stop
        // maintaining the interaction
        if let url = interaction.vidyoGuestURL, !url.isEmpty {
            onConnected(interaction)
            //return
        }
        
        if pollAttemptsRemaining == 0{
            onError("A Randox agent has not joined the room, please try agin later")
            return
        }
        
        // wait the set time and then check the interaction again
        // by passing the interaction back into maintain (this method)
        // we'll be checking if a randox agent has joibed or not
        DispatchQueue.main.asyncAfter(deadline: .now() + TimeInterval(POLL_TIME_INTERVAL_IN_SECONDS)) {
            check(
                interaction: interaction,
                withToken: token,
                withVidyoCredentials: vidyoCredentials,
                onSuccess: { (interaction) in
                    
                    maintain(
                        interaction: interaction,
                        withToken: token,
                        withVidyoCredentials: vidyoCredentials,
                        pollAttemptsRemaining: pollAttemptsRemaining - 1,
                        onConnected: onConnected,
                        onError: onError)
                    
            },
                onError: onError)
        }
    }
    static func getHeaders(_ token: String) -> HTTPHeaders{
        return ["Content-Type":"application/json",
                "Authorization": token]
    }
    // convenience method for appending access toekn and tenant id to url
    // this is wrong as it exposes the token on post calls but required by vidyo
    static func get(urlWithEndpoint endpoint:String, withVidyoCredentials vidyoCredentials:VidyoCredentials) -> String {
        let url = "\(BASE_URL)\(endpoint)?access_token=\(vidyoCredentials.apiKey!)&tenant=\(vidyoCredentials.tenant!)"
        return url
    }
    
    static func getWaitingRoomVideo(token:String, withVidyoCredentials vidyoCredentials:VidyoCredentials, onWaitingVideoFound: @escaping (_ waitingRoomVideo:WaitingRoomVideo) -> Void, onError: @escaping (_ error:String) -> Void){
        
        let header:HTTPHeaders = getHeaders(token)
        let url = get(urlWithEndpoint: "streamingVideo", withVidyoCredentials: vidyoCredentials)
        Alamofire.request(url, method: .get,  headers: header)
            .responseObject { (response: DataResponse<WaitingRoomVideo>) in
                
                guard let waitingRoomVideo = response.result.value else {
                    onError("An unexpected error occured, please try again later.")
                    return
                }
                
                onWaitingVideoFound(waitingRoomVideo)
        }
    }*/
}
