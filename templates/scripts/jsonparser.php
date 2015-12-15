<?php
class jsonparser {
        private $src = 'http://status.freifunk-myk.de/nodedata/nodes.json';

        private $cache = false;
        private $cache_node = array();

        function __construct() {
            $htmlcache = file_get_contents($this->src);
            $this->cache = json_decode($htmlcache);
            $this->gen_nodecache();
        }

        function gen_nodecache() {
            foreach($this->cache->nodes as $node) {
                $this->cache_node[base64_encode(strtoupper($node->nodeinfo->node_id))] = $node;
            }
            $this->cache=false;
        }

        function get_nodeinfo($mac) {
            $mac = strtoupper(str_replace(':', '', $mac));
            $data = array(
                'addresses' => array(''),
                'hardware' => 'unbekannt',
                'firmware' => 'unbekannt',
                'autoupdater_state' => false,
                'name' => 'unbekannt',
                'lastseen' => 0,
                'geo' => array(0,0),
                'ip' => ''
            );

            if(!isset($this->cache_node[base64_encode($mac)])) return $data;
            $info = $this->cache_node[base64_encode($mac)];

            $ip = '';
            if(isset($info->nodeinfo->network->addresses)) {
                foreach($info->nodeinfo->network->addresses as $tip) {
                    if(substr($tip, 0, 4) == '2a01') $ip = $tip;
                }
            }

            $data = array(
                'addresses' => $info->nodeinfo->network->addresses,
                'hardware' => $info->nodeinfo->hardware->model,
                'firmware' => $info->nodeinfo->software->firmware->release,
                'autoupdater_state' => $info->nodeinfo->software->autoupdater->enabled,
                'name' => $info->nodeinfo->hostname,
                'lastseen' => $info->lastseen,
                'geo' => $info->nodeinfo->location,
                'ip' => $ip
            );
            return $data;
        }
    }
