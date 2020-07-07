import { Component } from "@angular/core";
import {discardedErrorEvent, uncaughtErrorEvent, UnhandledErrorEventData, on as applicationOn, run as applicationRun } from "tns-core-modules/application";

@Component({
    selector: "ns-app",
    templateUrl: "./app.component.html"
})
export class AppComponent { 

    constructor( ) {
        applicationOn(uncaughtErrorEvent, (errData: UnhandledErrorEventData) => {
            console.log('caught error', errData);
        });
    }
}
