<?php

/*function getFirmwareList(WirePage $page){
  $children = $page->children;
  if(count($children)){ }else{return "Es existiert derzeit keine Firmware für diesen Router"};

  foreach($children as $firmware){
    $art = array();
    $version =
    $datum =
    $MD5 =
    $download =
    $size =

      <ul class='accordion' data-accordion>
        <li class='accordion-navigation'>
          <a href='#stable'>Stable</a>
          <div id='stable' class='content'>
            Wenn du einen Router mit Originalfirmware hast oder dir nicht sicher bist was genau du brauchst dann nimm die Factory-Firmware. Um deinen Router mit Freifunk-Firmware zu aktualisieren kannst du Sysupgread benutzen.
            <h4><span data-tooltip aria-haspopup='true' class='has-tip' title='Möchtest du deinen Router zum Freifunk-Router umfunktionieren bist du hier richtig.'>Factory</span></h4>
            <table class='firmware-download-list'>
              <thead>
                <tr>
                  <th width='50'>Version/<br/>Modell</th>
                  <th width='50'>Datum</th>
                  <th width='200'>MD5</th>
                  <th>Download</th>
                  <th width='50'>Größe</th>
                </tr>
              </thead>
              <tbody>
                <tr>
                  <td>v1</td>
                  <td>2015/09</td>
                  <td>bc4d277862322960c6ac948244796b08</td>
                  <td><a href='#'>gluon-ffmyk-0.7-stable-2015-09-09-tp-link-tl-wdr4300-v1.bin</a><br/>
                  </td>
                  <td>7.8M</td>
                </tr>
              </tbody>
            </table><!-- table factory -->
            <h4><span data-tooltip aria-haspopup='true' class='has-tip' title='Möchtest du deinen Freifunk-Router Aktualisieren dann ist Sysupgread die richtige Wahl.'>Sysupgread</span></h4>
            <table class='firmware-download-list'>
              <thead>
                <tr>
                  <th width='50'>Version/<br/>Modell</th>
                  <th width='50'>Datum</th>
                  <th>MD5</th>
                  <th>Download</th>
                  <th>Größe</th>
                </tr>
              </thead>
              <tbody>
                <tr>
                  <td>v1</td>
                  <td>2015/11/9</td>
                  <td>ed55573ebb33f626134807aafd173133</td>
                  <td><a href='#'>gluon-ffmyk-2015.1.2-nightly-2015-11-08-tp-link-tl-wdr4300-v1.bin</a></td>
                  <td>3.8M</td>
                </tr>
              </tbody>
            </table><!-- table sysupgread -->
          </div><!-- #stable -->
        </li><!-- #accordion stable -->
        <li class='accordion-navigation'>
          <a href='#nightly'>Nightly</a>
          <div id='nightly' class='content'>
            <h4>Factory</h4>
            <table class='firmware-download-list'>
              <thead>
                <tr>
                  <th width='50'>Version/<br/>Modell</th>
                  <th width='50'>Datum</th>
                  <th width='200'>MD5</th>
                  <th>Download</th>
                  <th width='50'>Größe</th>
                </tr>
              </thead>
              <tbody>
                <tr>
                  <td>v1</td>
                  <td>2015/11/11</td>
                  <td>bc4d277862322960c6ac948244796b08</td>
                  <td><a href='#'>gluon-ffmyk-0.7-stable-2015-09-09-tp-link-tl-wdr4300-v1.bin</a><br/>
                  </td>
                  <td>7.8M</td>
                </tr>
                <tr>
                  <td>v1</td>
                  <td>2015/11/10</td>
                  <td>bc4d277862322960c6ac948244796b08</td>
                  <td><a href='#'>gluon-ffmyk-0.7-stable-2015-09-09-tp-link-tl-wdr4300-v1.bin</a><br/>
                  </td>
                  <td>7.8M</td>
                </tr>
                <tr>
                  <td>v1</td>
                  <td>2015/11/09</td>
                  <td>bc4d277862322960c6ac948244796b08</td>
                  <td><a href='#'>gluon-ffmyk-0.7-stable-2015-09-09-tp-link-tl-wdr4300-v1.bin</a><br/>
                  </td>
                  <td>7.8M</td>
                </tr>
              </tbody>
            </table><!-- table fectory -->
            <h4>Sysupgread</h4>
            <table class='firmware-download-list'>
              <thead>
                <tr>
                  <th width='50'>Version/<br/>Modell</th>
                  <th width='50'>Datum</th>
                  <th>MD5</th>
                  <th>Download</th>
                  <th>Größe</th>
                </tr>
              </thead>
              <tbody>
                <tr>
                  <td>v1</td>
                  <td>2015/11/10</td>
                  <td>ed55573ebb33f626134807aafd173133</td>
                  <td><a href='#'>gluon-ffmyk-2015.1.2-nightly-2015-11-08-tp-link-tl-wdr4300-v1.bin</a></td>
                  <td>7.8M</td>
                </tr>
                <tr>
                  <td>v1</td>
                  <td>2015/11/9</td>
                  <td>ed55573ebb33f626134807aafd173133</td>
                  <td><a href='#'>gluon-ffmyk-2015.1.2-nightly-2015-11-08-tp-link-tl-wdr4300-v1.bin</a></td>
                  <td>7.8M</td>
                </tr>
              </tbody>
            </table><!-- table sysupgread -->
          </div><!-- #nightly -->
        </li><!-- nightly -->
      </ul><!-- #arcordion -->
    }
}

$firmware = getFirmwareList($page);*/
$content = renderPage();
