/**
 *  Child Ultrasonic Sensor
 *
 *  Copyright 2017 Daniel Ogorchock
 *
 *  Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except
 *  in compliance with the License. You may obtain a copy of the License at:
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software distributed under the License is distributed
 *  on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License
 *  for the specific language governing permissions and limitations under the License.
 *
 *  Change History:
 *
 *    Date        Who            What
 *    ----        ---            ----
 *    2018-06-02  Dan Ogorchock  Revised/Simplified for Hubitat Composite Driver Model
 *
 *
 *
 */
metadata {
	definition (name: "child_DistanceSensor", namespace: "OmniThing", author: "Dan Ogorchock") {
		capability "Contact Sensor"
        capability "Sensor"

		attribute "lastUpdated", "String"
	}

	tiles(scale: 2) {

	multiAttributeTile(name:"Door Status", type: "generic", width: 6, height: 4, canChangeIcon: true, canChangeColor: true){
			tileAttribute ("device.contact", key: "PRIMARY_CONTROL"){
				attributeState "open", label: "Open", action: 'contact.open', icon: 'st.doors.garage.garage-open', backgroundColor: '#28b463'
				attributeState "closed", label: "Closed", action: 'contact.closed', icon: 'st.doors.garage.garage-closed', backgroundColor: '#ff0000'
 			}
            tileAttribute("device.lastUpdated", key: "SECONDARY_CONTROL") {
    			attributeState("default", label:'    Last updated ${currentValue}',icon: "st.Health & Wellness.health9");
        	}
		}
    }
	preferences {

        input name: "openThreshold", type: "number", title: "Open", description: "Enter the maximum distance in inches when door is open", required: true
    }
}
def parse(def update) {


  log.debug "parsing $update"

  for( e in update)
    {
    	log.debug "e.key $e.key e.value $e.value openThreshold $openThreshold";

        if(e.key == "distance")
        {
            def tmpValue = e.value.isNumber() ?  (e.value as double) : null;
            def tmpThreshold = openThreshold.isNumber() ?  (openThreshold as double) : null;

            log.debug "tmpValue $tmpValue tmpThreshold $tmpThreshold";

            if(tmpValue != null && tmpValue < tmpThreshold)
            {
            	log.debug "sending event: name=${e.key} value=${'open'}";
            	sendEvent(name: "contact", value: "open", displayed: true);
            }
            else
            {
            	log.debug "sending event: name=${e.key} value=${'closed'}";
            	sendEvent(name: "contact", value: "closed", displayed: true);
            }

        }
    }

    def nowDay = new Date().format("MMM dd", location.timeZone)
    def nowTime = new Date().format("h:mm a", location.timeZone)
    sendEvent(name: "lastUpdated", value: nowDay + " at " + nowTime, displayed: true)

    sendEvent(name: "distance", value: tmpValue, displayed: true)
}

def installed() {
}
