"use strict";
import { Component, OnInit  } from "@angular/core";
import { uncaughtErrorEvent, UnhandledErrorEventData, on as applicationOn, run as applicationRun } from "tns-core-modules/application";



@Component({
    selector: "ns-app",
    templateUrl: "./app.component.html"
})
export class AppComponent implements OnInit  {

    ngOnInit() : void
    {
        applicationOn(uncaughtErrorEvent, function (args: UnhandledErrorEventData) {
            console.log("Error: " + args.error);
        });
    }
 }
