#!/usr/bin/python

import argparse
import urllib.request
import os
import re
from urllib.parse import urljoin
from queue import Empty

class pywget:
    
    def __init__(self, url, max_depth):
        try:
            web_title = urllib.request.urlparse(url).hostname
            print("Crawling though: " + web_title);
        except:
            print("ERROR: Can't process url {} ".format(url))
            exit()
        else:
            if max_depth > 0: 
                self.visited = []
                self.copy_web_pages(url, max_depth)
            else:
                print("ERROR: Depth must be greater than 0 ")
                exit()
                                       
            
    def grab_data(self, url):
        """
        Fetch data from the requested url
        """
        headers = {'User-Agent':'Mozilla/5.0 (X11; U; Linux i686) Gecko/20071127 Firefox/2.0.0.11'}  # fake my identity
        try:
            self.url_parse = urllib.request.urlparse(url)
            request = urllib.request.Request(url, headers=headers)
            url_data = urllib.request.urlopen(request).read()
        except:
            print("ERROR: Can't process url {}".format(url))
            exit()
        else:
            return url_data
         
         
    def set_local_path(self):
        """
        Setup local directory reformatting, when necessary, the web url
        """
        current_dir = os.getcwd()
        print("Current dir: " + current_dir)
        
        web_file_path = re.sub(r'/[^/.\w]', '', self.url_parse.path)  # remove non alphanumeric characters form path
        print("Reformatted web file path:\t" + web_file_path)
               
        print(self.url_parse.hostname)
        web_file_path = (os.path.join(self.url_parse.hostname, web_file_path))
        print("Web file path:\t" + web_file_path)
        
        self.filename = os.path.split(web_file_path)[-1]
        print("Web file name:\t" + self.filename)
        
        web_dir_path = os.path.dirname(web_file_path)
        self.local_path = os.path.join(current_dir, web_dir_path)
        print("New local path:\t" + self.local_path)
                
        if not os.path.isdir(self.local_path):
            try:
                os.makedirs(self.local_path)
            except:
                print("ERROR: Can't create directory {} ".format(self.local_path))
                exit()
            else:
                print("New directory created successfully: {}".format(self.local_path))
        else:
            print ("Directory already exists. Nothing to be done here.") 
            
            
    def checkCollisions(self):
        """
        Check and solve collisions: Collisions are handled by inserting .​x ​before the file’s extension.
        """
        print("Checking for collisions ...")
        if os.path.exists(os.path.join(self.local_path, self.filename)):
            print("File-name already exists: ")
#             filename_split = os.path.splitext(self.filename)
            self.filename = self.version_up(self.local_path, self.filename, 1)
            print("New local file renamed to:\t" + self.filename)
            print("New local path renamed to:\t" + os.path.join(self.local_path, self.filename))


    def version_up(self, file_path, file_name, version):
        """
        Increase the version of the file to avoid overwriting
        """
        filename_zero = os.path.splitext(file_name)
        new_file = os.path.join(file_path, filename_zero[0] + '.' + str(version) + filename_zero[1])
        # find the next version up available
        if not (os.path.exists(os.path.join(file_path, new_file))):
            return (new_file)
        else:
            return self.version_up(file_path, file_name, version + 1)
#         
    
    def copy_source_code(self, url):
        """
        Copy the source-code from web url onto local directory
        """         
        url_data = self.grab_data(url)
        self.set_local_path()
        self.checkCollisions()

        try:
            sourceFile = open(os.path.join(self.local_path, self.filename), "wb")
            sourceFile.write(url_data)
        except IOError:
                print("Error: can\'t find file or read data")
        else:
            print("Written content in the file successfully")
            sourceFile.close()
            
            
    def copy_web_pages(self, url, max_depth):
        
        depth = 0
        
        # Copy the main page
        url_data = self.grab_data(url)
        url_data_decode = url_data.decode('utf8')
        self.copy_source_code(url)  # copy the url page
        self.visited.append(url)
        
        # Crawl though the links and download pages
        links = re.findall('<a href="?([^\s^"]+)', url_data_decode)
    
        for link in links:
            if not urllib.request.urlparse(link).netloc:  # local path -> add prefix
                link = urljoin(url, link)
                print(link)
                if link not in self.visited:
#                     self.visited.append(link)
                    self.copy_web_page(link, depth + 1, max_depth)
                else:
                    print("Link already visited {}".format(link))
            elif urllib.request.urlparse(link).netloc == urllib.request.urlparse(url).hostname:  # external path
                print(link)
                if link not in self.visited:
#                     self.visited.append(link)
                    self.copy_web_page(link, depth + 1, max_depth)
                else:
                    print("Link already visited {}".format(link))
            else:
                print("Link is external to this domain. Skip.. {}".format(link))
        
            
    def copy_web_page(self, url, depth, max_depth):
        
        if depth <= max_depth: 
            # Copy the main page
            url_data = self.grab_data(url)
            url_data_decode = url_data.decode('utf8')
            self.visited.append(url) # add  this url to the visited set
            self.copy_source_code(url) # copy the url page
    
            # Crawl though the links and download pages
            links = re.findall('<a href="?([^\s^"]+)', url_data_decode)
            images = re.findall('<img src="?([^\s^"]+)', url_data_decode)
                            
            for image in images:
                if not urllib.request.urlparse(image).netloc:
                    image = urljoin(url, image)
                    self.copy_source_code(image)
                    print(image)
                elif urllib.request.urlparse(image).netloc == urllib.request.urlparse(url).hostname:
                    self.copy_source_code(image)
                    print(image)
                else:
                    print("Link is external to this domain. Skip.. {}".format(image))
                
            for link in links: # recursively process childs
                if not urllib.request.urlparse(link).netloc: # local path
                    link = urljoin(url, link)
                    if not link in self.visited:
                        self.copy_web_page(link, depth + 1, max_depth)
                    else:
                        print("Link already visited {}".format(link))
                elif urllib.request.urlparse(link).netloc == urllib.request.urlparse(url).hostname: # external path
                    if not link in self.visited:
                        self.copy_web_page(link, depth + 1, max_depth)
                    else:
                        print("Link already visited {}".format(link))
                else:
                    print("Link is external to this domain. Skip.. {}".format(link))
            
        else:
            print("Reached maximum depth: {}".format(max_depth))
            return
         

def main():
    parser = argparse.ArgumentParser(description="python web crawler")
    parser.add_argument('--url', '-u', type=str, help='Url to be crawled', default="http://homepages.ecs.vuw.ac.nz/~ian/nwen241/index.html")
    parser.add_argument('--max_depth', '-d', type=int, help='Max depth levels which means go into links on a page till depth level', default=2)
    args = parser.parse_args()
    pywget(args.url, args.max_depth)
            
if __name__ == '__main__':
    main()  
