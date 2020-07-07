import { Component, OnInit } from "@angular/core";
import { ActivatedRoute, ResolveEnd } from "@angular/router";

import { Item } from "./item";
import { ItemService } from "./item.service";

import { knownFolders, Folder, File,path } from "tns-core-modules/file-system";
import * as dialogs from "tns-core-modules/ui/dialogs";
import {discardedErrorEvent, uncaughtErrorEvent, UnhandledErrorEventData, on as applicationOn, run as applicationRun } from "tns-core-modules/application";

//import Initialize from "../../../typings/arm64/objc!IDCardToolkit.ts";

declare var Toolkit: any;
declare var Initialize:any;
declare var IDCardToolkit:any;
declare var MyClass:any;

@Component({
    selector: "ns-details",
    templateUrl: "./item-detail.component.html",
})
export class ItemDetailComponent implements OnInit {
    item: Item;

    constructor(
        private itemService: ItemService,
        private route: ActivatedRoute
    ) {}

    ngOnInit():void {           
            const id = +this.route.snapshot.params.id;
            this.item = this.itemService.getItem(id);
    }
   
    onTap(args)
    {
        const myClassInstance = new MyClass();
        let configFolderPath = myClassInstance.logInfo();            

        const documents: Folder = <Folder>knownFolders.documents();
        const folder: Folder = <Folder>documents.getFolder("config");

        let configParams = "config_directory =" + configFolderPath + "/" + "\n";
        configParams += "&log_directory =" + configFolderPath + "/" + "\n";         
        configParams += "&read_publicdata_offline = true" + "\n"; 
                   
        var objToolkit = Toolkit.new();
       
        try{
        var toolkit = objToolkit.initConfigParamsError(1,configParams.toString());
    }
    catch(e)
    {
        dialogs.alert(e).then(function() {
            console.log("Dialog closed!");
        });
        console.log(e);
    }
    }
}
