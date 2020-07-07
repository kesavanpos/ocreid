import { Component, OnInit } from "@angular/core";
import { ActivatedRoute } from "@angular/router";
import { knownFolders, Folder, File } from "tns-core-modules/file-system";
import { Item } from "./item";
import { ItemService } from "./item.service";
import * as dialogs from "tns-core-modules/ui/dialogs";
declare var Toolkit: any;

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

    async ngOnInit() {
        try{
            debugger;
            const id = +this.route.snapshot.params.id;
            this.item = this.itemService.getItem(id);

            const documents: Folder = <Folder>knownFolders.documents();
            const folder: Folder = <Folder>documents.getFolder("config");

            let configParams = "config_directory =" + folder.path + "\n";
            //configParams += "&log_directory =" + folder.path  + "\n";
            configParams += "&vg_url=http://172.16.11.13/ValidationGatewayService"  + "\n";            
        

            let configdirectory = "config_directory" + folder.path;
            let log = "log_directory =" +folder.path;
            let vgurl = "vg_url=http://172.16.11.13/ValidationGatewayService" ;


            //var toolkit = new Toolkit({config_directory:configdirectory,logdirectory: log,vg_url:vgurl});
            var objToolkit = Toolkit.new();
            var toolkit1 = await new Toolkit().initConfigParamsError(0,configParams);                        

            //var toolkit = new Toolkit().initConfigParamsError(configdirectory,log,vgurl);                        
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
