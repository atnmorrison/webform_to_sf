Webform to Salesforce
===

## Overview 

The webform to salesforce module enables webform to send data to salesforce including attachments. A corresponding public webservice needs to be setup on the target salesforce instance. You can install the webservice from this unmanaged package on the appexchange

Production:
https://login.salesforce.com/packaging/installPackage.apexp?p0=04t6A000000OVKw

Sandbox:
https:/test.salesforce.com/packaging/installPackage.apexp?p0=04t6A000000OVKw

## Installation 

Install the module in the appropriate module folder for your site or include it in your make file 

## Contributors

Scott Morrison

## Usage

To use the module make sure your user has the appropriate permissions. Create webform content and you should now see a Send to Salesforce tab. To enable send to salesforce for your form click the tab and click enable. Enter the target service location where the data will be sent, this must be a valid url that knows how to handle the JSON post request from the form. Select the SObject that the data will be written to, in most cases this will be Lead but any object could be used. When creating the form make sure that the fields that you want to capture in salesforce have the api name of the field on as the key for the form element. View and test your from by submitting data. Log into salesforce and ensure that the data was captured. All file attachments will be sent to salesforce and attached to the record that was created 