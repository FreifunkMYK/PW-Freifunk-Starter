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
            <th width='50'>Community</th>
            <th width='50'>Release</th>
            <th width='200'>MD5</th>
            <th>Download</th>
          </tr>
        </thead>
        <tbody>
          <?=$stableFactory?>
        </tbody>
      </table><!-- table factory -->
      <h4><span data-tooltip aria-haspopup='true' class='has-tip' title='Möchtest du deinen Freifunk-Router Aktualisieren dann ist Sysupgread die richtige Wahl.'>Sysupgrade</span></h4>
      <table class='firmware-download-list'>
        <thead>
          <tr>
            <th width='50'>Version/<br/>Modell</th>
            <th width='50'>Community</th>
            <th>Release</th>
            <th>MD5</th>
            <th>Download</th>
          </tr>
        </thead>
        <tbody>
          <?=$stableSysupgrade?>
        </tbody>
      </table><!-- table sysupgread -->
    </div><!-- #stable -->
  </li><!-- #accordion stable -->
  <li class='accordion-navigation'>
    <a href='#nightly'>Beta</a>
    <div id='nightly' class='content'>
      <h4><span data-tooltip aria-haspopup='true' class='has-tip' title='Möchtest du deinen Router zum Freifunk-Router umfunktionieren bist du hier richtig.'>Factory</span></h4>
      <table class='firmware-download-list'>
        <thead>
          <tr>
            <th width='50'>Version/<br/>Modell</th>
            <th width='50'>Community</th>
            <th width='50'>Release</th>
            <th width='200'>MD5</th>
            <th>Download</th>
          </tr>
        </thead>
        <tbody>
          <?=$betaFactory?>
        </tbody>
      </table><!-- table fectory -->
      <h4><span data-tooltip aria-haspopup='true' class='has-tip' title='Möchtest du deinen Freifunk-Router Aktualisieren dann ist Sysupgread die richtige Wahl.'>Sysupgrade</span></h4>
      <table class='firmware-download-list'>
        <thead>
          <tr>
            <th width='50'>Version/<br/>Modell</th>
            <th width='50'>Community</th>
            <th width='50'>Release</th>
            <th>MD5</th>
            <th>Download</th>
          </tr>
        </thead>
        <tbody>
          <?=$betaSysupgrade?>
        </tbody>
      </table><!-- table sysupgread -->
    </div><!-- #nightly -->
  </li><!-- nightly -->
</ul><!-- #arcordion -->
