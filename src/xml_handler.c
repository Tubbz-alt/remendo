/*
 * xml_handler.c
 *
 * Copyright (C) 2013 - Alex Filgueira
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "xml_handler.h"

void get_events(xmlDocPtr doc, xmlNodePtr cur, char *subchild){
    xmlChar *key=NULL;
    cur = cur->xmlChildrenNode;
    while(cur != NULL){
        if((!xmlStrcmp(cur->name, (const xmlChar *)subchild))){
			key = xmlNodeListGetString(doc,cur->xmlChildrenNode, 1);
			printf("%s\n", key);
			xmlFree(key);
		}
        cur = cur->next;
    }
}

int parse_xml(char *xml_file, char *child, char *subchild){
    xmlDocPtr doc;
    xmlNodePtr cur;

    doc = xmlParseFile(xml_file);
    if (doc == NULL) {
        fprintf(stderr, "Failed to parse %s\n", xml_file);
    return;
    }

    cur = xmlDocGetRootElement(doc);

    if (cur == NULL){
        fprintf(stderr, "Empty document\n");
        xmlFreeDoc(doc);
        return;
    }

    cur = cur->xmlChildrenNode;
    while(cur != NULL){
        if((!xmlStrcmp(cur->name, (const xmlChar *)child))){
            get_events(doc,cur,subchild);
        }
        cur = cur->next;
    }
    xmlFreeDoc(doc);
}